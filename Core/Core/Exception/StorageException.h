#ifndef VORTEX_CORE_EXCEPTION_STORAGEEXCEPTION_H
#define VORTEX_CORE_EXCEPTION_STORAGEEXCEPTION_H

#include <Core/Exception/VortexException.h>

namespace Vortex {
	namespace Core {
		namespace Exception {
			class StorageException : public VortexException {
			public:
				StorageException(const std::string& message, const std::string& details = "");
			};
		}  // namespace Exception
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_EXCEPTION_STORAGEEXCEPTION_H
