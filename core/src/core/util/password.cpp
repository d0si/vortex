#include <core/util/password.h>
#include <core/util/random.h>
#ifdef VORTEX_HAS_FEATURE_CRYPTOPP
#include <cryptopp/sha.h>
#include <cryptopp/base64.h>
#endif
#define SALT_LENGTH 24

namespace vortex {
namespace core {
namespace util {
namespace password {

std::string hash_password(std::string password) {
  return hash_password(password, generate_salt());
}

std::string hash_password(std::string password, std::string salt, unsigned int iterations) {
#ifdef VORTEX_HAS_FEATURE_CRYPTOPP
  if (salt.empty()) {
    salt = generate_salt();
  }

  CryptoPP::byte* salt_bytes = (CryptoPP::byte*) salt.c_str();

  std::string hash_string = salt + password;

  CryptoPP::SHA256 hash;
  CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
  hash.CalculateDigest(digest, (CryptoPP::byte*) hash_string.c_str(), hash_string.length());

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
  throw std::exception("VORTEX_HAS_FEATURE_CRYPTOPP is not defined. Crypto++ features are not available.");
#endif
}

bool verify_password(std::string password, std::string hashed_password) {
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
    } else {
      if (current_char == '$') {
        reading_hash = true;
      } else {
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

std::string generate_salt() {
#ifdef VORTEX_HAS_FEATURE_CRYPTOPP
  CryptoPP::byte salt[SALT_LENGTH];

  if (util::random::rand_bytes(salt, SALT_LENGTH) != 0) {
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
  throw std::exception("VORTEX_HAS_FEATURE_CRYPTOPP is not defined. Crypto++ features are not available.");
#endif
}

}  // namespace password
}  // namespace util
}  // namespace core
}  // namespace vortex
