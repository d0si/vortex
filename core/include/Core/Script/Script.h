#ifndef VORTEX_CORE_SCRIPT_SCRIPT_H
#define VORTEX_CORE_SCRIPT_SCRIPT_H

#include <string>
#include <core/script/duktape.h>

namespace Vortex {
	namespace Core {
		class Framework;

		namespace Script {
			class Script {
			private:
				Framework* framework_;
				Duktape duktape_;

			public:
				Script(Framework* framework);

				void setup();
				void exec(std::string script);
			};
		}  // namespace Script
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_SCRIPT_SCRIPT_H
