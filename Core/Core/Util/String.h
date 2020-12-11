#ifndef VORTEX_CORE_UTIL_STRING_H
#define VORTEX_CORE_UTIL_STRING_H

#include <string>
#include <vector>
#include <Core/DLLSupport.h>

namespace Vortex {
	namespace Core {
		namespace Util {
			namespace String {
				std::string VORTEX_CORE_API join(const std::vector<std::string>& values, const std::string& separator);
				std::vector<std::string> VORTEX_CORE_API split(const std::string& value, const std::string& delimiter);

				std::string VORTEX_CORE_API trim(const std::string& value);
				std::string VORTEX_CORE_API trim_left(const std::string& value);
				std::string VORTEX_CORE_API trim_right(const std::string& value);

				bool VORTEX_CORE_API contains(const std::string& value, const std::string& search);
				bool VORTEX_CORE_API starts_with(const std::string& value, const std::string& search);
				bool VORTEX_CORE_API ends_with(const std::string& value, const std::string& search);
			}  // namespace String
		}  // namespace Util
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_UTIL_STRING_H
