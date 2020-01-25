#include <core/util/hash.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>

namespace vortex {
namespace core {
namespace util {
namespace hash {

std::string sha1(const std::string& value) {
    return sha1((const unsigned char*)value.c_str(), value.length());
}

std::string sha1(unsigned char* value, size_t length) {
    unsigned char digest[CryptoPP::SHA1::DIGESTSIZE];

    CryptoPP::SHA1 hash;
    hash.CalculateDigest(digest, value, length);

    return hex_encode(digest, CryptoPP::SHA1::DIGESTSIZE);
}

std::string sha256(const std::string& value) {
    return sha256((const unsigned char*)value.c_str(), value.length());
}

std::string sha256(const unsigned char* value, const size_t length) {
    unsigned char digest[CryptoPP::SHA256::DIGESTSIZE];

    CryptoPP::SHA256 hash;
    hash.CalculateDigest(digest, value, length);

    return hex_encode(digest, CryptoPP::SHA256::DIGESTSIZE);
}

std::string sha512(const std::string value) {
    return sha512((const unsigned char*)value.c_str(), value.length());
}

std::string sha512(const unsigned char* value, const size_t length) {
    unsigned char digest[CryptoPP::SHA512::DIGESTSIZE];

    CryptoPP::SHA512 hash;
    hash.CalculateDigest(digest, value, length);

    return hex_encode(digest, CryptoPP::SHA512::DIGESTSIZE);
}

std::string md5(const std::string value) {
    return md5((const unsigned char*)value.c_str(), value.length());
}

std::string md5(const unsigned char* value, const size_t length) {
    unsigned char digest[CryptoPP::Weak::MD5::DIGESTSIZE];

    CryptoPP::Weak::MD5 hash;
    hash.CalculateDigest(digest, value, length);

    return hex_encode(digest, CryptoPP::Weak::MD5::DIGESTSIZE);
}

std::string hex_encode(const unsigned char* value, size_t length) {
    CryptoPP::HexEncoder encoder(nullptr, false);
    std::string output;

    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(value, length);
    encoder.MessageEnd();

    return output;
}

}  // namespace hash
}  // namespace util
}  // namespace core
}  // namespace vortex
