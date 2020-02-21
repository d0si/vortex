#include <core/script/script.h>
#include <core/framework/framework.h>

namespace vortex {
	namespace core {
		namespace script {
			Script::Script(framework::Framework* framework)
				: framework_(framework), duktape_(framework) {

			}

			void Script::setup() {
				duktape_.setup();
			}

			void Script::exec(std::string script) {
				duktape_.exec(script);
			}
		}  // namespace script
	}  // namespace core
}  // namespace vortex
