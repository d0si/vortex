#include <VortexFramework/VortexModule.h>
#include <VortexFramework/Framework.h>
#include <Core/Modules/DependencyInjection.h>

using namespace Vortex::Core;
using namespace Vortex::Core::Modules;

namespace Vortex::VortexFramework {

    const std::string VortexModule::s_module_name = "VortexModule";

    const std::string VortexModule::module_name() const {
        return s_module_name;
    }

    const std::vector<std::string> VortexModule::plugin_names() {
        return std::vector<std::string> {
            //Plugins::Plugin0::s_plugin_name,
        };
    }

    Plugin* VortexModule::plugin(const std::string& plugin_name) {
        /*if (plugin_name == Plugins::Plugin0::s_plugin_name)
            return new Plugins::Plugin0;*/

        return nullptr;
    }

    void VortexModule::register_di(DependencyInjector* di) {
        di->install([](const Maze::Element& config, std::string client_ip, boost::beast::http::request<boost::beast::http::string_body>* request, boost::beast::http::response<boost::beast::http::string_body>* response) {
            return (FrameworkInterface*)new Framework(config, client_ip, request, response);
            });
    }

}

VORTEX_APP_API Module* get_vortex_module() {
    return new Vortex::VortexFramework::VortexModule;
}

VORTEX_APP_API const char* get_vortex_module_name() {
    return Vortex::VortexFramework::VortexModule::s_module_name.c_str();
}
