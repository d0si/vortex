#pragma once

#include <string>
#include <Core/DLLSupport.hpp>

namespace Vortex::Core::Util::Random {

    VORTEX_CORE_API const std::string random_string(const unsigned int length = 32, const std::string& char_list = "0123456789" "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    VORTEX_CORE_API int rand_bytes(void* const byte_buf, const unsigned int byte_len);

}  // namespace Vortex::Core::Util::Random
