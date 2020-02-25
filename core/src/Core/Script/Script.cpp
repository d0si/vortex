#include <core/script/script.h>
#include <core/framework.h>

namespace Vortex {
	namespace Core {
		namespace Script {
			Script::Script(Framework* framework)
				: framework_(framework), duktape_(framework) {

			}

			void Script::setup() {
				duktape_.setup();
			}

			void Script::exec(std::string script) {
				duktape_.exec(script);
			}
		}  // namespace Script
	}  // namespace Core
}  // namespace Vortex
