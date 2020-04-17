#ifndef VORTEX_CORE_SCRIPT_ISCRIPTENGINE_H
#define VORTEX_CORE_SCRIPT_ISCRIPTENGINE_H

#include <string>

namespace Vortex {
	namespace Core {
		class Framework;

		namespace Script {
			class IScriptEngine {
			private:
				Framework* framework_;

			public:
				IScriptEngine() {};
				virtual ~IScriptEngine() {};

				virtual void setup(Framework* framework) = 0;
				virtual void exec(const std::string& script) = 0;
			};

			typedef IScriptEngine* (*GetScriptEngineInstanceFunc)();

			struct ScriptEngineDetails {
				const char* class_name;
				const char* engine_name;
				GetScriptEngineInstanceFunc get_new_engine_instance;
			};
		}  // namespace Script
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_SCRIPT_ISCRIPTENGINE_H
