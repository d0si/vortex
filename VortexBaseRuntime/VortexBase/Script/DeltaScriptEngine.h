#pragma once

#include <VortexBase/Script/Script.h>

namespace DeltaScript {
	class Context;
}

namespace VortexBase::Script {

	class DeltaScriptEngine : public ScriptEngineInterface {
	public:
		DeltaScriptEngine();
		~DeltaScriptEngine();

		virtual void init(Vortex::Core::RuntimeInterface* runtime) override;
		virtual void exec(const std::string& script) override;

	private:
		DeltaScript::Context* _ctx = nullptr;
	};

	
	ScriptEngineInterface* get_new_deltascript_engine();


	static const ScriptEngineDetails deltascript_exports = {
		"DeltaScriptEngine",
		"DeltaScript",
		get_new_deltascript_engine
	};

}  // namespace VortexBase::Script
