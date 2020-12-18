#pragma once

#include <string>
#include <Core/DLLSupport.hpp>

namespace Vortex::Core::Util::Password {

    VORTEX_CORE_API const std::string hash_password(const std::string& password);
    VORTEX_CORE_API const std::string hash_password(const std::string& password, const std::string& salt, const unsigned int iterations = 100000);
    VORTEX_CORE_API bool verify_password(const std::string& password, const std::string& hashed_password);
    VORTEX_CORE_API const std::string generate_salt();

}  // namespace Vortex::Core::Util::Password 
