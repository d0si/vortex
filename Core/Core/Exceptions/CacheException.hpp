#pragma once

#include <Core/Exceptions/VortexException.hpp>

namespace Vortex::Core::Exceptions {

    class CacheException : public VortexException {
    public:
        VORTEX_CORE_API CacheException(const std::string& message);
        VORTEX_CORE_API CacheException(const std::string& message, const std::string& details);
    };

}  // namespace Vortex::Core::Exceptions
