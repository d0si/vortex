#include <Core/Script/Script.h>
#include <Core/Framework.h>
#ifdef HAS_FEATURE_DUKTAPE
#include <Core/Script/DuktapeEngine.h>
#endif
#ifdef HAS_FEATURE_DELTASCRIPT
#include <Core/Script/DeltaScriptEngine.h>
#endif
#include <Core/Script/DummyEngine.h>
#include <Core/Exceptions/ScriptException.h>
#include <iostream>

namespace Vortex::Core::Script {

	Script::Script(Framework* framework)
		: _framework(framework) {}

	Script::~Script() {
		if (_initialized_engine)
			delete _initialized_engine;
	}

	void Script::setup() {
		const Maze::Element& script_config = _framework->config()->get("script");
#ifdef HAS_FEATURE_DELTASCRIPT
		_default_engine_name = "DeltaScript";
#elif defined(HAS_FEATURE_DUKTAPE)
		_default_engine_name = Core::Script::duktape_exports.engine_name;
#endif

		if (script_config.is_object("javascript")) {
			if (script_config["javascript"].is_string("default_engine")) {
				_default_engine_name = script_config["javascript"]["default_engine"].get_string();
			}
		}

#ifdef HAS_FEATURE_DELTASCRIPT
		if (_default_engine_name == Core::Script::deltascript_exports.engine_name) {
			_initialized_engine = Core::Script::deltascript_exports.get_new_engine_instance();
		}
#endif

#ifdef HAS_FEATURE_DUKTAPE
		if (_default_engine_name == Core::Script::duktape_exports.engine_name) {
			_initialized_engine = Core::Script::duktape_exports.get_new_engine_instance();
		}
#endif

		if (_default_engine_name == Core::Script::dummy_exports.engine_name) {
			std::cout << "WARNING: Using Dummy script engine. Scripting will not be available." << std::endl;
			_initialized_engine = Core::Script::dummy_exports.get_new_engine_instance();
		}

		if (_initialized_engine == nullptr) {
			throw Exceptions::ScriptException("Default script engine unavailable");
		}

		_initialized_engine->setup(_framework);
	}

	void Script::exec(const std::string& script) {
		_initialized_engine->exec(script);
	}

}
