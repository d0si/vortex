#pragma once

#include <Core/VortexModule/Script/Script.h>

namespace Vortex::Core::VortexModule::Script {

	class DummyEngine : public ScriptEngineInterface {
	public:
		virtual void init(FrameworkInterface* framework) override;
		virtual void exec(const std::string& script) override;
	};


	ScriptEngineInterface* get_new_dummy_engine();


	static const ScriptEngineDetails dummy_exports = {
		"DummyEngine",
		"Dummy",
		get_new_dummy_engine
	};

}  // namespace Vortex::Core::VortexModule::Script
