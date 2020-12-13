#pragma once

#include <VortexFramework/Script/Script.h>

namespace duk {
	class Context;
}

namespace Vortex::VortexFramework::Script {

	class DuktapeEngine : public ScriptEngineInterface {
	public:
		DuktapeEngine();
		~DuktapeEngine();

		virtual void init(Core::FrameworkInterface* framework) override;
		virtual void exec(const std::string& script) override;

	private:
		duk::Context* _ctx = nullptr;
	};


	ScriptEngineInterface* get_new_duktape_engine();


	static const ScriptEngineDetails duktape_exports = {
		"DuktapeEngine",
		"Duktape",
		get_new_duktape_engine
	};

}  // namespace Vortex::VortexFramework::Script
