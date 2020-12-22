#include "DbApplicationPlugin.h"
#include <Core/Interfaces.h>
#include <Core/Util/String.h>

namespace Vortex::App::Db::Plugins {

    const std::string DbApplicationPlugin::s_plugin_name = "DbApplicationPlugin";

    const std::string DbApplicationPlugin::plugin_name() const {
        return s_plugin_name;
    }

    Vortex::Core::Modules::PluginExecutePoint DbApplicationPlugin::execute_point() {
        return Vortex::Core::Modules::PluginExecutePoint::APPLICATION_INIT;
    }

    /*bool DbApplicationPlugin::execute_before(Vortex::Core::RuntimeInterface* runtime) {
        return false;
    }*/

}
