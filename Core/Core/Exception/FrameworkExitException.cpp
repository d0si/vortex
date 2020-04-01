#include <Core/Exception/FrameworkExitException.h>

namespace Vortex {
	namespace Core {
		namespace Exception {
			FrameworkExitException::FrameworkExitException(const std::string& message, const std::string& details) : VortexException("Framework exit: " + message, details) {

			}
		}  // namespace Exception
	}  // namespace Core
}  // namespace Vortex

