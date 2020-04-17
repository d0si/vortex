#ifndef VORTEX_CORE_SCRIPT_SCRIPT_H
#define VORTEX_CORE_SCRIPT_SCRIPT_H

#include <string>

namespace Vortex {
	namespace Core {
		class Framework;

		namespace Script {
			class IScriptEngine;

			class Script {
			private:
				Framework* framework_;
				IScriptEngine* initialized_engine_ = nullptr;
				std::string default_engine_name_ = "Dummy";

			public:
				Script(Framework* framework);
				~Script();

				void setup();
				void exec(const std::string& script);
			};
		}  // namespace Script
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_SCRIPT_SCRIPT_H
