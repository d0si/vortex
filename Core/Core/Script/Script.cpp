#include <Core/Script/Script.h>
#include <Core/Framework.h>
#include <Core/Script/IScriptEngine.h>
#ifdef VORTEX_HAS_FEATURE_DUKTAPE
#include <Core/Script/DuktapeEngine.h>
#endif
#ifdef VORTEX_HAS_FEATURE_DELTASCRIPT
#include <Core/Script/DeltaScriptEngine.h>
#endif
#include <Core/Script/DummyEngine.h>
#include <Core/Exception/VortexException.h>
#include <iostream>

namespace Vortex {
	namespace Core {
		namespace Script {
			Script::Script(Framework* framework)
				: framework_(framework) {
			}

			Script::~Script() {
				if (initialized_engine_)
					delete initialized_engine_;
			}

			void Script::setup() {
				const Maze::Element& script_config = framework_->get_config().get("script");
#ifdef VORTEX_HAS_FEATURE_DELTASCRIPT
				default_engine_name_ = "DeltaScript";
#elif defined(VORTEX_HAS_FEATURE_DUKTAPE)
				default_engine_name_ = Core::Script::duktape_exports.engine_name;
#endif

				if (script_config.is_object("javascript")) {
					if (script_config["javascript"].is_string("default_engine")) {
						default_engine_name_ = script_config["javascript"]["default_engine"].get_string();
					}
				}

#ifdef VORTEX_HAS_FEATURE_DELTASCRIPT
				if (default_engine_name_ == Core::Script::deltascript_exports.engine_name) {
					initialized_engine_ = Core::Script::deltascript_exports.get_new_engine_instance();
				}
#endif

#ifdef VORTEX_HAS_FEATURE_DUKTAPE
				if (default_engine_name_ == Core::Script::duktape_exports.engine_name) {
					initialized_engine_ = Core::Script::duktape_exports.get_new_engine_instance();
				}
#endif

				if (default_engine_name_ == Core::Script::dummy_exports.engine_name) {
					std::cout << "WARNING: Using Dummy script engine. Scripting will not be available." << std::endl;
					initialized_engine_ = Core::Script::dummy_exports.get_new_engine_instance();
				}

				if (initialized_engine_ == nullptr) {
					throw Exception::VortexException("Default script engine unavailable");
				}

				initialized_engine_->setup(framework_);
			}

			void Script::exec(const std::string& script) {
				initialized_engine_->exec(script);
			}
		}  // namespace Script
	}  // namespace Core
}  // namespace Vortex
