#pragma once

#include <string>
#include <Core/DLLSupport.hpp>

namespace Vortex::Core::Util::Hash {

    VORTEX_CORE_API std::string sha1(const std::string& value);
    VORTEX_CORE_API std::string sha1(const unsigned char* value, const size_t length);
    VORTEX_CORE_API std::string sha256(const std::string& value);
    VORTEX_CORE_API std::string sha256(const unsigned char* value, const size_t length);
    VORTEX_CORE_API std::string sha512(const std::string& value);
    VORTEX_CORE_API std::string sha512(const unsigned char* value, const size_t length);
    VORTEX_CORE_API std::string md5(const std::string& value);
    VORTEX_CORE_API std::string md5(const unsigned char* value, const size_t length);

    VORTEX_CORE_API std::string hex_encode(const unsigned char* value, const size_t length);

}  // namespace Vortex::Core::Util::Hash
