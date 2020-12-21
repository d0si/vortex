#pragma once

#include <Core/Exceptions/VortexException.h>

namespace Vortex::Core::Exceptions {

    class ScriptException : public VortexException {
    public:
        VORTEX_CORE_API ScriptException(const std::string& message);
        VORTEX_CORE_API ScriptException(const std::string& message, const std::string& details);
    };

}  // namespace Vortex::Core::Exceptions
