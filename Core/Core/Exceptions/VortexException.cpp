#include <Core/Exceptions/VortexException.h>
#include <sstream>

namespace Vortex::Core::Exceptions {

    VortexException::VortexException(const std::string& message)
        : VortexException(message, "") {}

    VortexException::VortexException(const std::string& message, const std::string& details)
        : VortexException(message, details, "Vortex") {}

    VortexException::VortexException(const std::string& message, const std::string& details, const std::string& category)
        : _message(message), _details(details), _category(category) {
        _what = (std::stringstream()
            << "(" << _category << ") "
            << _message
            << " - "
            << _details).str();
    }

    inline char const* VortexException::what() const noexcept {
        return _what.c_str();
    }

}
