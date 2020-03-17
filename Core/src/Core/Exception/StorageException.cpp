#include <Core/Exception/StorageException.h>

namespace Vortex {
	namespace Core {
		namespace Exception {
			StorageException::StorageException(const std::string& message, const std::string& details) : VortexException("Storage: " + message, details) {

			}
		}  // namespace Exception
	}  // namespace Core
}  // namespace Vortex
