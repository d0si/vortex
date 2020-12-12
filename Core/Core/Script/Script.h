#pragma once

#include <string>
#include <Core/DLLSupport.h>

namespace Vortex::Core {

    class Framework;

}  // Vortex::Core

namespace Vortex::Core::Script {

    class ScriptEngineInterface {
    public:
        VORTEX_CORE_API ScriptEngineInterface() = default;
        VORTEX_CORE_API virtual ~ScriptEngineInterface() = default;

        VORTEX_CORE_API virtual void setup(Framework* framework) = 0;
        VORTEX_CORE_API virtual void exec(const std::string& script) = 0;

    private:
        Framework* _framework = nullptr;
    };


    typedef ScriptEngineInterface* (*GetScriptEngineInstanceFunction)();


    struct ScriptEngineDetails {
        const char* class_name;
        const char* engine_name;
        GetScriptEngineInstanceFunction get_new_engine_instance;
    };


    class Script {
    public:
        VORTEX_CORE_API Script(Framework* framework);
        VORTEX_CORE_API ~Script();

        VORTEX_CORE_API void setup();
        VORTEX_CORE_API void exec(const std::string& script);

    private:
        Framework* _framework;
        ScriptEngineInterface* _initialized_engine = nullptr;
        std::string _default_engine_name = "Dummy";
    };

}  // namespace Vortex::Core::Script
