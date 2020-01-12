#ifndef VORTEX_CORE_UTIL_PASSWORD_H
#define VORTEX_CORE_UTIL_PASSWORD_H

#include <string>

namespace vortex {
namespace core {
namespace util {
namespace password {

std::string hash_password(std::string password);
std::string hash_password(std::string password, std::string salt, unsigned int iterations = 100000);
bool verify_password(std::string password, std::string hash);
std::string generate_salt();

}  // namespace password
}  // namespace util
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_UTIL_PASSWORD_H
