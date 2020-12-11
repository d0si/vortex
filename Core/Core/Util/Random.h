#ifndef VORTEX_CORE_UTIL_RANDOM_H
#define VORTEX_CORE_UTIL_RANDOM_H

#include <string>
#include <Core/DLLSupport.h>

namespace Vortex {
	namespace Core {
		namespace Util {
			namespace Random {
				std::string VORTEX_CORE_API random_string(unsigned int length = 32, const std::string char_list = "0123456789" "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
				int VORTEX_CORE_API rand_bytes(void* const byte_buf, const size_t byte_len);
			}  // namespace Random
		}  // namespace Util
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_UTIL_RANDOM_H
