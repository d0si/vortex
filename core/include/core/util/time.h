#ifndef VORTEX_CORE_UTIL_TIME_H
#define VORTEX_CORE_UTIL_TIME_H

#include <string>

namespace vortex {
namespace core {
namespace util {
namespace time {

int get_now();
int get_diff(int time);
int get_diff(int time_1, int time_2);
std::string to_string(int time);
std::string get_now_string();

}  // namespace time
}  // namespace util
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_UTIL_TIME_H
