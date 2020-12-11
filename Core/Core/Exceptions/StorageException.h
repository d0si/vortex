#pragma once

#include <Core/Exceptions/VortexException.h>

namespace Vortex::Core::Exceptions {

    class StorageException : public VortexException {
    public:
        VORTEX_CORE_API StorageException(const std::string& message);
        VORTEX_CORE_API StorageException(const std::string& message, const std::string& details);
    };

}  // namespace Vortex::Core::Exceptions
