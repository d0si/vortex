#pragma once

#include <Core/Script/Script.h>

namespace DeltaScript {
	class Context;
}

namespace Vortex::Core::Script {

	class DeltaScriptEngine : public ScriptEngineInterface {
	public:
		DeltaScriptEngine();
		~DeltaScriptEngine();

		virtual void setup(Framework* framework) override;
		virtual void exec(const std::string& script) override;

	private:
		DeltaScript::Context* _ctx = nullptr;
		Framework* _framework;
	};

	
	ScriptEngineInterface* get_new_deltascript_engine();


	static const ScriptEngineDetails deltascript_exports = {
		"DeltaScriptEngine",
		"DeltaScript",
		get_new_deltascript_engine
	};

}  // namespace Vortex::Core::Script
