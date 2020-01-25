#ifndef VORTEX_CORE_UTIL_HASH_H
#define VORTEX_CORE_UTIL_HASH_H

#include <string>

namespace vortex {
namespace core {
namespace util {
namespace hash {

std::string sha1(const std::string& value);
std::string sha1(const unsigned char* value, const size_t length);
std::string sha256(const std::string& value);
std::string sha256(const unsigned char* value, const size_t length);
std::string sha512(const std::string& value);
std::string sha512(const unsigned char* value, const size_t length);
std::string md5(const std::string& value);
std::string md5(const unsigned char* value, const size_t length);

std::string hex_encode(const unsigned char* value, const size_t length);

}  // namespace hash
}  // namespace util
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_UTIL_HASH_H
