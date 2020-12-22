#include "DbRouterPlugin.h"

namespace Vortex::App::Db::Plugins {

    const std::string DbRouterPlugin::s_plugin_name = "DbRouterPlugin";

    const std::string DbRouterPlugin::plugin_name() const {
        return s_plugin_name;
    }

    Vortex::Core::Modules::PluginExecutePoint DbRouterPlugin::execute_point() {
        return Vortex::Core::Modules::PluginExecutePoint::ROUTER_INIT;
    }

    bool DbRouterPlugin::execute_before(Vortex::Core::RuntimeInterface* runtime) {
        return false;
    }

    bool DbRouterPlugin::execute_after(Vortex::Core::RuntimeInterface* runtime) {
        return false;
    }

}
