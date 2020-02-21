#ifndef VORTEX_CORE_UTIL_RANDOM_H
#define VORTEX_CORE_UTIL_RANDOM_H

#include <string>

namespace vortex {
	namespace core {
		namespace util {
			namespace random {
				std::string random_string(unsigned int length = 32, const std::string char_list = "0123456789" "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
				int rand_bytes(void* const byte_buf, const size_t byte_len);
			}  // namespace random
		}  // namespace util
	}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_UTIL_RANDOM_H
