#include <core/util/hash.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

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

}  // namespace hash
}  // namespace util
}  // namespace core
}  // namespace vortex
