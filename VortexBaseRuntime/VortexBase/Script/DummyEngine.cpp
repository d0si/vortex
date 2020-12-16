#include <VortexBase/Script/DummyEngine.h>

namespace VortexBase::Script {

    void DummyEngine::init(Vortex::Core::RuntimeInterface* runtime) {}

    void DummyEngine::exec(const std::string& script) {}

    
    ScriptEngineInterface* get_new_dummy_engine() {
        return new DummyEngine();
    }

}
