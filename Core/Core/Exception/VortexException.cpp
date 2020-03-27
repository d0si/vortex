#include <Core/Exception/VortexException.h>

namespace Vortex {
	namespace Core {
		namespace Exception {
			VortexException::VortexException(const std::string& message, const std::string& details) : message(message), details(details) {

			}
		}  // namespace Exception
	}  // namespace Core
}  // namespace Vortex
