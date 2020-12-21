#include <Core/Exceptions/ScriptException.h>

namespace Vortex::Core::Exceptions {

	ScriptException::ScriptException(const std::string& message)
		: VortexException(message, "") {}

	ScriptException::ScriptException(const std::string& message, const std::string& details)
		: VortexException(message, details, "Script") {}

}
