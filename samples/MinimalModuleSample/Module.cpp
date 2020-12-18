#include "Module.h"

using namespace Vortex::Core::Modules;

namespace ModuleSample {

    const std::string SampleModule::s_module_name = "MinimalModuleSample";

    const std::string SampleModule::module_name() const {
        return s_module_name;
    }

    const std::vector<std::string> SampleModule::plugin_names() {
        return std::vector<std::string>();
    }

    Plugin* SampleModule::plugin(const std::string& plugin_name) {
        return nullptr;
    }

    void SampleModule::register_di(const std::shared_ptr<DependencyInjector>& di) {}
}

VORTEX_APP_API Module* get_vortex_module() {
    return new ModuleSample::SampleModule;
}

VORTEX_APP_API const char* get_vortex_module_name() {
    return ModuleSample::SampleModule::s_module_name.c_str();
}
