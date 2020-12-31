#pragma once

#include <VortexBase/Script/Script.h>

namespace duk {
	class Context;
}

namespace VortexBase::Script {

	class DuktapeEngine : public ScriptEngineInterface {
	public:
		DuktapeEngine();
		~DuktapeEngine();

		virtual void init(Vortex::Core::RuntimeInterface* runtime) override;
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

}  // namespace VortexBase::Script
