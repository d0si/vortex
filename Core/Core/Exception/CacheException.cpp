#include <Core/Exception/CacheException.h>

namespace Vortex {
	namespace Core {
		namespace Exception {
			CacheException::CacheException(const std::string& message, const std::string& details) : VortexException("Cache: " + message, details) {

			}
		}  // namespace Exception
	}  // namespace Core
}  // namespace Vortex
