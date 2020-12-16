#pragma once

#include <Core/Script/Script.h>

namespace Vortex::Core::Script {

	class DummyEngine : public ScriptEngineInterface {
	public:
		virtual void setup(Framework* framework) override;
		virtual void exec(const std::string& script) override;
	};


	ScriptEngineInterface* get_new_dummy_engine();


	static const ScriptEngineDetails dummy_exports = {
		"DummyEngine",
		"Dummy",
		get_new_dummy_engine
	};

}
