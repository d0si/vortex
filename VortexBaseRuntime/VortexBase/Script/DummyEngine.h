#pragma once

#include <VortexBase/Script/Script.h>

namespace VortexBase::Script {

	class DummyEngine : public ScriptEngineInterface {
	public:
		virtual void init(Vortex::Core::RuntimeInterface* runtime) override;
		virtual void exec(const std::string& script) override;
	};


	ScriptEngineInterface* get_new_dummy_engine();


	static const ScriptEngineDetails dummy_exports = {
		"DummyEngine",
		"Dummy",
		get_new_dummy_engine
	};

}  // namespace VortexBase::Script
