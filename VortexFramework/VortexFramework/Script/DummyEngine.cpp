#include <VortexFramework/Script/DummyEngine.h>

namespace Vortex::VortexFramework::Script {

    void DummyEngine::init(Core::FrameworkInterface* framework) {}

    void DummyEngine::exec(const std::string& script) {}

    
    ScriptEngineInterface* get_new_dummy_engine() {
        return new DummyEngine();
    }

}
