#pragma once

#include <string>
#include <Core/DLLSupport.h>
#include <Core/Interfaces.h>

namespace Vortex::Core::VortexModule::Script {

    class ScriptEngineInterface {
    public:
        VORTEX_CORE_API ScriptEngineInterface() = default;
        VORTEX_CORE_API virtual ~ScriptEngineInterface() = default;

        VORTEX_CORE_API virtual void init(FrameworkInterface* framework) = 0;
        VORTEX_CORE_API virtual void exec(const std::string& script) = 0;

    protected:
        FrameworkInterface* _framework = nullptr;
    };


    typedef ScriptEngineInterface* (*GetScriptEngineInstanceFunction)();


    struct ScriptEngineDetails {
        const char* class_name;
        const char* engine_name;
        GetScriptEngineInstanceFunction get_new_engine_instance;
    };


    class Script : public ScriptInterface {
    public:
        VORTEX_CORE_API Script(FrameworkInterface* framework);
        VORTEX_CORE_API virtual ~Script();

        VORTEX_CORE_API virtual void init() override;
        VORTEX_CORE_API virtual void exec(const std::string& script) override;

    private:
        ScriptEngineInterface* _initialized_engine = nullptr;
        std::string _default_engine_name = "Dummy";
    };

}  // namespace Vortex::Core::VortexModule::Script
