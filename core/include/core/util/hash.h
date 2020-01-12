#ifndef VORTEX_CORE_UTIL_HASH_H
#define VORTEX_CORE_UTIL_HASH_H

#include <string>

namespace vortex {
namespace core {
namespace util {
namespace hash {

std::string sha1(std::string value);
std::string md5(std::string value);

}  // namespace hash
}  // namespace util
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_UTIL_HASH_H
