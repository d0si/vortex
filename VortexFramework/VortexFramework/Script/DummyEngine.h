#pragma once

#include <VortexFramework/Script/Script.h>

namespace Vortex::VortexFramework::Script {

	class DummyEngine : public ScriptEngineInterface {
	public:
		virtual void init(Core::FrameworkInterface* framework) override;
		virtual void exec(const std::string& script) override;
	};


	ScriptEngineInterface* get_new_dummy_engine();


	static const ScriptEngineDetails dummy_exports = {
		"DummyEngine",
		"Dummy",
		get_new_dummy_engine
	};

}  // namespace Vortex::VortexFramework::Script
