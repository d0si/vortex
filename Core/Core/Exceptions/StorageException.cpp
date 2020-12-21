#include <Core/Exceptions/StorageException.h>
#include <stdio.h>

namespace Vortex::Core::Exceptions {

    StorageException::StorageException(const std::string& message)
        : StorageException(message, "") {}

    StorageException::StorageException(const std::string& message, const std::string& details)
        : VortexException(message, details, "Storage") {}

}
