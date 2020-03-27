#ifndef VORTEX_CORE_EXCEPTION_CACHEEXCEPTION_H
#define VORTEX_CORE_EXCEPTION_CACHEEXCEPTION_H

#include <Core/Exception/VortexException.h>

namespace Vortex {
	namespace Core {
		namespace Exception {
			class CacheException : public VortexException {
			public:
				CacheException(const std::string& message, const std::string& details = "");
			};
		}  // namespace Exception
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_EXCEPTION_CACHEEXCEPTION_H
