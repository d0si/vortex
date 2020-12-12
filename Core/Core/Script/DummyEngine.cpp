#include <Core/Script/DummyEngine.h>

namespace Vortex::Core::Script {

    void DummyEngine::setup(Framework* framework) {}

    void DummyEngine::exec(const std::string& script) {}

    
    ScriptEngineInterface* get_new_dummy_engine() {
        return new DummyEngine();
    }

}
