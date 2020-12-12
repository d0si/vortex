#include "DbSitePlugin.h"

namespace Vortex::App::Db::Plugins {

    const std::string DbSitePlugin::s_plugin_name = "DbSitePlugin";

    const std::string DbSitePlugin::plugin_name() const {
        return s_plugin_name;
    }

}
