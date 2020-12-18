#include <Core/Util/String.hpp>
#include <boost/algorithm/string.hpp>

namespace Vortex::Core::Util {

    const std::string String::join(const std::vector<std::string>& values, const std::string& separator) {
        if (values.size() == 0)
            return std::string();

        return boost::algorithm::join(values, separator);
    }

    std::vector<std::string> String::split(const std::string& value, const std::string& delimiter) {
        std::vector<std::string> results;
        return boost::algorithm::split(results, value, boost::is_any_of(delimiter));
    }

    const std::string String::trim(const std::string& value) {
        return boost::algorithm::trim_copy(value);
    }

    const std::string String::trim_left(const std::string& value) {
        return boost::algorithm::trim_left_copy(value);
    }

    const std::string String::trim_right(const std::string& value) {
        return boost::algorithm::trim_right_copy(value);
    }

    bool String::contains(const std::string& value, const std::string& search) {
        return boost::algorithm::contains(value, search);
    }

    bool String::starts_with(const std::string& value, const std::string& search) {
        return boost::algorithm::starts_with(value, search);
    }

    bool String::ends_with(const std::string& value, const std::string& search) {
        return boost::algorithm::ends_with(value, search);
    }

}
