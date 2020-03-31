#ifndef VORTEX_CORE_FRAMEWORK_USER_H
#define VORTEX_CORE_FRAMEWORK_USER_H

#include <string>

namespace Vortex {
	namespace Core {
		class Framework;

		class User {
		private:
			Framework* framework_;

		public:
			User(Framework* framework);
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_USER_H
