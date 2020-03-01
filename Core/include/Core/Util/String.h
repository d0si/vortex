#ifndef VORTEX_CORE_UTIL_STRING_H
#define VORTEX_CORE_UTIL_STRING_H

#include <string>
#include <vector>

namespace Vortex {
	namespace Core {
		namespace Util {
			namespace String {
				std::string join(const std::vector<std::string>& values, const std::string& separator);
				std::vector<std::string> split(const std::string& value, const std::string& delimiter);

				std::string trim(const std::string& value);
				std::string trim_start(const std::string& value);
				std::string trim_end(const std::string& value);

				bool contains(const std::string& value, const std::string& search);
				bool starts_with(const std::string& value, const std::string& search);
				bool ends_with(const std::string& value, const std::string& search);
			}  // namespace String
		}  // namespace Util
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_UTIL_STRING_H
