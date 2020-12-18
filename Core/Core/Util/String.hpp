#pragma once

#include <string>
#include <vector>
#include <Core/DLLSupport.hpp>

namespace Vortex::Core::Util::String {

    VORTEX_CORE_API const std::string join(const std::vector<std::string>& values, const std::string& separator);
    VORTEX_CORE_API std::vector<std::string> split(const std::string& value, const std::string& delimiter);

    VORTEX_CORE_API const std::string trim(const std::string& value);
    VORTEX_CORE_API const std::string trim_left(const std::string& value);
    VORTEX_CORE_API const std::string trim_right(const std::string& value);

    VORTEX_CORE_API bool contains(const std::string& value, const std::string& search);
    VORTEX_CORE_API bool starts_with(const std::string& value, const std::string& search);
    VORTEX_CORE_API bool ends_with(const std::string& value, const std::string& search);

}  // namespace Vortex::Core::Util::String
