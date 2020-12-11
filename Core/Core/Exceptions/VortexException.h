#pragma once

#include <exception>
#include <string>
#include <Core/DLLSupport.h>

namespace Vortex::Core::Exceptions {

    class VortexException : public std::exception {
    public:
        VORTEX_CORE_API VortexException(const std::string& message);
        VORTEX_CORE_API VortexException(const std::string& message, const std::string& details);
        VORTEX_CORE_API VortexException(const std::string& message, const std::string& details, const std::string& category);

        VORTEX_CORE_API const std::string& message() { return _message; }
        VORTEX_CORE_API const std::string& details() { return _details; }
        VORTEX_CORE_API const std::string& category() { return _category; }

        VORTEX_CORE_API virtual const char* what() const override;

    private:
        std::string _message;
        std::string _details;
        std::string _category;

        std::string _what;
    };

}  // namespace Vortex::Core::Exceptions
