#ifndef VORTEX_CORE_SCRIPT_DUMMYENGINE_H
#define VORTEX_CORE_SCRIPT_DUMMYENGINE_H

#include <Core/Script/IScriptEngine.h>

namespace Vortex {
	namespace Core {
		namespace Script {
			class DummyEngine : public IScriptEngine {
			public:
				virtual void setup(Framework* framework) { }
				virtual void exec(const std::string& script) { }
			};

			IScriptEngine* get_new_dummy_engine() {
				return new DummyEngine();
			}

			static const ScriptEngineDetails dummy_exports = {
				"DummyEngine",
				"Dummy",
				get_new_dummy_engine
			};
		}  // namespace Script
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_SCRIPT_DUMMYENGINE_H
