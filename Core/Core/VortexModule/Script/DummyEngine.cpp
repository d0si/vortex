#include <Core/VortexModule/Script/DummyEngine.h>

namespace Vortex::Core::VortexModule::Script {

    void DummyEngine::init(FrameworkInterface* framework) {}

    void DummyEngine::exec(const std::string& script) {}

    
    ScriptEngineInterface* get_new_dummy_engine() {
        return new DummyEngine();
    }

}
