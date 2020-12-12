#pragma once

#include <string>
#include <Core/Script/Script.h>

namespace duk {
	class Context;
}

namespace Vortex::Core {
	class Framework;
}

namespace Vortex::Core::Script {

	class DuktapeEngine : public ScriptEngineInterface {
	public:
		DuktapeEngine();
		~DuktapeEngine();

		virtual void setup(Framework* framework) override;
		virtual void exec(const std::string& script) override;

	private:
		duk::Context* _ctx = nullptr;
		Framework* _framework = nullptr;
	};


	ScriptEngineInterface* get_new_duktape_engine();


	static const ScriptEngineDetails duktape_exports = {
		"DuktapeEngine",
		"Duktape",
		get_new_duktape_engine
	};

}
