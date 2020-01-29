#ifndef VORTEX_CORE_UTIL_STRING_H
#define VORTEX_CORE_UTIL_STRING_H

#include <string>
#include <vector>

namespace vortex {
namespace core {
namespace util {
namespace string {

std::string join(const std::vector<std::string>& values, const std::string& separator);
std::vector<std::string> split(const std::string& value, const std::string& delimiter);

std::string trim(const std::string& value);
std::string trim_start(const std::string& value);
std::string trim_end(const std::string& value);

bool contains(const std::string& value, const std::string& search);
bool starts_with(const std::string& value, const std::string& search);
bool ends_with(const std::string& value, const std::string& search);

}  // namespace string
}  // namespace util
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_UTIL_STRING_H
