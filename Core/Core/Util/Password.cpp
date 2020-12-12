#include <Core/Util/Password.h>
#include <stdexcept>
#include <Core/Util/Random.h>
#ifdef HAS_FEATURE_CRYPTOPP
#include <cryptopp/sha.h>
#include <cryptopp/base64.h>
#endif
#define SALT_LENGTH 24

namespace Vortex::Core::Util {

    const std::string Password::hash_password(const std::string& password) {
        return hash_password(password, generate_salt());
    }

    const std::string Password::hash_password(const std::string& password, std::string& salt, const unsigned int iterations) {
#ifdef HAS_FEATURE_CRYPTOPP
        if (salt.empty()) {
            salt = generate_salt();
        }

        CryptoPP::byte* salt_bytes = (CryptoPP::byte*)salt.c_str();

        std::string hash_string = salt + password;

        CryptoPP::SHA256 hash;
        CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
        hash.CalculateDigest(digest, (CryptoPP::byte*)hash_string.c_str(), hash_string.length());

        for (unsigned int i = 1; i < iterations; ++i) {
            CryptoPP::byte intermediate[CryptoPP::SHA256::DIGESTSIZE + sizeof(salt_bytes)];

            memcpy(intermediate, digest, CryptoPP::SHA256::DIGESTSIZE);
            memcpy(intermediate + CryptoPP::SHA256::DIGESTSIZE, salt_bytes, sizeof(salt_bytes));

            hash.CalculateDigest(digest, intermediate, sizeof(intermediate));
        }

        std::string hash_output;
        CryptoPP::Base64Encoder encoder;
        CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters(CryptoPP::Name::InsertLineBreaks(), false);
        encoder.IsolatedInitialize(params);
        encoder.Attach(new CryptoPP::StringSink(hash_output));
        encoder.Put(digest, sizeof(digest));
        encoder.MessageEnd();

        return "$v1$" + salt + "$" + hash_output;
#else
        throw std::runtime_error("HAS_FEATURE_CRYPTOPP is not defined. Crypto++ features are not available.");
#endif
    }

    bool Password::verify_password(const std::string& password, const std::string& hashed_password) {
        if (hashed_password.length() < 80 || hashed_password.substr(0, 4) != "$v1$") {
            return false;
        }

        std::string salt;
        std::string hash;
        bool reading_hash = false;
        char current_char;
        for (unsigned int i = 4; i < hashed_password.length(); ++i) {
            current_char = hashed_password[i];

            if (reading_hash) {
                hash += current_char;
            }
            else {
                if (current_char == '$') {
                    reading_hash = true;
                }
                else {
                    salt += current_char;
                }
            }
        }

        if (salt.empty() || salt.length() != SALT_LENGTH || hash.empty()) {
            return false;
        }

        std::string new_password_hash = hash_password(password, salt);

        return new_password_hash == hashed_password;
    }

    std::string Password::generate_salt() {
#ifdef HAS_FEATURE_CRYPTOPP
        CryptoPP::byte salt[SALT_LENGTH];

        if (Util::Random::rand_bytes(salt, SALT_LENGTH) != 0) {
            return "";
        }

        std::string salt_str;

        CryptoPP::Base64Encoder encoder;
        CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters(CryptoPP::Name::InsertLineBreaks(), false);
        encoder.IsolatedInitialize(params);
        encoder.Attach(new CryptoPP::StringSink(salt_str));
        encoder.Put(salt, sizeof(salt));
        encoder.MessageEnd();

        return salt_str;
#else
        throw std::runtime_error("HAS_FEATURE_CRYPTOPP is not defined. Crypto++ features are not available.");
#endif
    }

}
