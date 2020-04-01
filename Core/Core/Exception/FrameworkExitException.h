#ifndef VORTEX_CORE_EXCEPTION_FRAMEWORKEXITEXCEPTION_H
#define VORTEX_CORE_EXCEPTION_FRAMEWORKEXITEXCEPTION_H

#include <Core/Exception/VortexException.h>

namespace Vortex {
	namespace Core {
		namespace Exception {
			class FrameworkExitException : public VortexException {
			public:
				FrameworkExitException(const std::string& message, const std::string& details = "");
			};
		}  // namespace Exception
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_EXCEPTION_FRAMEWORKEXITEXCEPTION_H
