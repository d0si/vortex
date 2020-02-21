#ifndef VORTEX_CORE_SCRIPT_SCRIPT_H
#define VORTEX_CORE_SCRIPT_SCRIPT_H

#include <string>
#include <core/script/duktape.h>

namespace vortex {
	namespace core {
		namespace framework {
			class Framework;
		}

		namespace script {
			class Script {
			private:
				framework::Framework* framework_;
				Duktape duktape_;

			public:
				Script(framework::Framework* framework);

				void setup();
				void exec(std::string script);
			};
		}  // namespace script
	}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_SCRIPT_SCRIPT_H
