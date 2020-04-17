#ifndef VORTEX_CORE_SCRIPT_DUKTAPEENGINE_H
#define VORTEX_CORE_SCRIPT_DUKTAPEENGINE_H

#include <string>
#include <Core/Script/IScriptEngine.h>

namespace duk {
	class Context;
}

namespace Vortex {
	namespace Core {
		class Framework;

		namespace Script {
			class DuktapeEngine : public IScriptEngine {
			private:
				duk::Context* ctx_;
				Framework* framework_;

			public:
				DuktapeEngine();
				~DuktapeEngine();

				virtual void setup(Framework* framework);
				virtual void exec(const std::string& script);
			};

			IScriptEngine* get_new_duktape_engine();

			static const ScriptEngineDetails duktape_exports = {
				"DuktapeEngine",
				"Duktape",
				get_new_duktape_engine
			};
		}  // namespace Script
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_SCRIPT_DUKTAPEENGINE_H
