#include <core/util/hash.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>

namespace vortex {
namespace core {
namespace util {
namespace hash {

std::string sha1(std::string value) {
    CryptoPP::byte digest[CryptoPP::SHA1::DIGESTSIZE];

    CryptoPP::SHA1 hash;
    hash.CalculateDigest(digest, (const CryptoPP::byte*) value.c_str(), value.length());

    CryptoPP::HexEncoder encoder(nullptr, false);
    std::string output;

    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return output;
}

std::string md5(std::string value) {
    CryptoPP::byte digest[CryptoPP::Weak::MD5::DIGESTSIZE];

    CryptoPP::Weak::MD5 hash;
    hash.CalculateDigest(digest, (const CryptoPP::byte*) value.c_str(), value.length());

    CryptoPP::HexEncoder encoder(nullptr, false);
    std::string output;

    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return output;
}

}  // namespace hash
}  // namespace util
}  // namespace core
}  // namespace vortex
