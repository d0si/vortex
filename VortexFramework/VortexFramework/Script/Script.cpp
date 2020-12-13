#include <VortexFramework/Script/Script.h>
#ifdef HAS_FEATURE_DUKTAPE
#include <VortexFramework/Script/DuktapeEngine.h>
#endif
#ifdef HAS_FEATURE_DELTASCRIPT
#include <VortexFramework/Script/DeltaScriptEngine.h>
#endif
#include <VortexFramework/Script/DummyEngine.h>
#include <Core/Exceptions/ScriptException.h>
#include <iostream> // TODO: Move output into logger

using namespace Vortex::Core;

namespace Vortex::VortexFramework::Script {

	Script::Script(FrameworkInterface* framework)
		: ScriptInterface(framework) {}

	Script::~Script() {
		if (_initialized_engine)
			delete _initialized_engine;
	}

	void Script::init() {
		const Maze::Element& script_config = _framework->config()->get("script");
#ifdef HAS_FEATURE_DELTASCRIPT
		_default_engine_name = "DeltaScript";
#elif defined(HAS_FEATURE_DUKTAPE)
		_default_engine_name = VortexFramework::Script::duktape_exports.engine_name;
#endif

		if (script_config.is_object("javascript")) {
			if (script_config["javascript"].is_string("default_engine")) {
				_default_engine_name = script_config["javascript"]["default_engine"].get_string();
			}
		}

#ifdef HAS_FEATURE_DELTASCRIPT
		if (_default_engine_name == VortexFramework::Script::deltascript_exports.engine_name) {
			_initialized_engine = VortexFramework::Script::deltascript_exports.get_new_engine_instance();
		}
#endif

#ifdef HAS_FEATURE_DUKTAPE
		if (_default_engine_name == VortexFramework::Script::duktape_exports.engine_name) {
			_initialized_engine = VortexFramework::Script::duktape_exports.get_new_engine_instance();
		}
#endif

		if (_default_engine_name == VortexFramework::Script::dummy_exports.engine_name) {
			std::cout << "WARNING: Using Dummy script engine. Scripting will not be available." << std::endl;
			_initialized_engine = VortexFramework::Script::dummy_exports.get_new_engine_instance();
		}

		if (_initialized_engine == nullptr) {
			throw Exceptions::ScriptException("Default script engine unavailable");
		}

		_initialized_engine->init(_framework);
	}

	void Script::exec(const std::string& script) {
		_initialized_engine->exec(script);
	}

}
