#include <VortexBase/VortexBaseRuntimeModule.h>
#include <VortexBase/BaseRuntime.h>
#include <Core/Modules/DependencyInjection.h>

using namespace Vortex::Core;
using namespace Vortex::Core::Modules;

namespace VortexBase {

    const std::string VortexBaseRuntimeModule::s_module_name = "VortexBaseRuntimeModule";

    const std::string VortexBaseRuntimeModule::module_name() const {
        return s_module_name;
    }

    const std::vector<std::string> VortexBaseRuntimeModule::plugin_names() {
        return std::vector<std::string> {
            //Plugins::Plugin0::s_plugin_name,
        };
    }

    Plugin* VortexBaseRuntimeModule::plugin(const std::string& plugin_name) {
        /*if (plugin_name == Plugins::Plugin0::s_plugin_name)
            return new Plugins::Plugin0;*/

        return nullptr;
    }

    void VortexBaseRuntimeModule::register_di(const std::shared_ptr<DependencyInjector>& di) {
        di->install([](const std::shared_ptr<DependencyInjector>& di, const Maze::Element& config, std::string client_ip, boost::beast::http::request<boost::beast::http::string_body>* request, boost::beast::http::response<boost::beast::http::string_body>* response) {
            return (std::shared_ptr<RuntimeInterface>)std::make_shared<BaseRuntime>(config, client_ip, request, response);
            });
    }

}

VORTEX_APP_API Module* get_vortex_module() {
    return new VortexBase::VortexBaseRuntimeModule;
}

VORTEX_APP_API const char* get_vortex_module_name() {
    return VortexBase::VortexBaseRuntimeModule::s_module_name.c_str();
}
