#ifndef VORTEX_CORE_UTIL_TIME_H
#define VORTEX_CORE_UTIL_TIME_H

#include <string>
#include <Core/DLLSupport.h>

namespace Vortex {
	namespace Core {
		namespace Util {
			namespace Time {
				int VORTEX_CORE_API get_now();
				int VORTEX_CORE_API get_diff(int time);
				int VORTEX_CORE_API get_diff(int time_1, int time_2);
				std::string VORTEX_CORE_API to_string(int time);
				std::string VORTEX_CORE_API get_now_string();
			}  // namespace Time
		}  // namespace Util
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_UTIL_TIME_H
