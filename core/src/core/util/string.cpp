#include <core/util/string.h>
#include <boost/algorithm/string.hpp>

namespace vortex {
	namespace core {
		namespace util {
			namespace string {
				std::string join(const std::vector<std::string>& values, const std::string& separator) {
					if (values.size() == 0)
						return std::string();

					return boost::algorithm::join(values, separator);
				}

				std::vector<std::string> split(const std::string& value, const std::string& delimiter) {
					std::vector<std::string> results;
					return boost::algorithm::split(results, value, boost::is_any_of(delimiter));
				}

				std::string trim(const std::string& value) {
					return boost::algorithm::trim_copy(value);
				}

				std::string trim_left(const std::string& value) {
					return boost::algorithm::trim_left_copy(value);
				}

				std::string trim_right(const std::string& value) {
					return boost::algorithm::trim_right_copy(value);
				}

				bool contains(const std::string& value, const std::string& search) {
					return boost::algorithm::contains(value, search);
				}

				bool starts_with(const std::string& value, const std::string& search) {
					return boost::algorithm::starts_with(value, search);
				}

				bool ends_with(const std::string& value, const std::string& search) {
					return boost::algorithm::ends_with(value, search);
				}
			}  // namespace string
		}  // namespace util
	}  // namespace core
}  // namespace vortex
