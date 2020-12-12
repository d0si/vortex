#include "DbApplicationPlugin.h"

namespace Vortex::App::Db::Plugins {

    const std::string DbApplicationPlugin::s_plugin_name = "DbApplicationPlugin";

    const std::string DbApplicationPlugin::plugin_name() const {
        return s_plugin_name;
    }

}
