#pragma once

#include <string>
#include <Core/DLLSupport.hpp>

namespace Vortex::Core::Util::Time {

    VORTEX_CORE_API int get_now();
    VORTEX_CORE_API int get_diff(const int time);
    VORTEX_CORE_API int get_diff(const int time_1, const int time_2);
    VORTEX_CORE_API const std::string to_string(const int time);
    VORTEX_CORE_API const std::string get_now_string();

}  // namespace Vortex::Core::Util::Time
