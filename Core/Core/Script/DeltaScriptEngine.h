#ifndef VORTEX_CORE_SCRIPT_DELTASCRIPTENGINE_H
#define VORTEX_CORE_SCRIPT_DELTASCRIPTENGINE_H

#include <Core/Script/IScriptEngine.h>

namespace DeltaScript {
	class Context;
}

namespace Vortex {
	namespace Core {
		namespace Script {
			class DeltaScriptEngine : public IScriptEngine {
			private:
				DeltaScript::Context* ctx_ = nullptr;
				Framework* framework_;

			public:
				DeltaScriptEngine();
				~DeltaScriptEngine();

				void setup(Framework* framework);
				void exec(const std::string& script);
			};

			IScriptEngine* get_new_deltascript_engine();

			static const ScriptEngineDetails deltascript_exports = {
				"DeltaScriptEngine",
				"DeltaScript",
				get_new_deltascript_engine
			};
		}  // namespace Script
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_SCRIPT_DELTASCRIPTENGINE_H
