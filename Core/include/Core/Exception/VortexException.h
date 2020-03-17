#ifndef VORTEX_CORE_EXCEPTION_VORTEXEXCEPTION_H
#define VORTEX_CORE_EXCEPTION_VORTEXEXCEPTION_H

#include <exception>
#include <string>

namespace Vortex {
	namespace Core {
		namespace Exception {
			class VortexException : public std::exception {
			public:
				const std::string message;
				const std::string details;

				VortexException(const std::string& message, const std::string& details = "");
			};
		}  // namespace Exception
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_EXCEPTION_VORTEXEXCEPTION_H
