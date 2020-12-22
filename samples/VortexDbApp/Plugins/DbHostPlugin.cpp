#include "DbHostPlugin.h"
#include <Core/Interfaces.h>
#include <Core/Util/String.h>

namespace Vortex::App::Db::Plugins {

    const std::string DbHostPlugin::s_plugin_name = "DbHostPlugin";

    const std::string DbHostPlugin::plugin_name() const {
        return s_plugin_name;
    }

    Vortex::Core::Modules::PluginExecutePoint DbHostPlugin::execute_point() {
        return Vortex::Core::Modules::PluginExecutePoint::APPLICATION_INIT;
    }

    bool DbHostPlugin::execute_before(Vortex::Core::RuntimeInterface* runtime) {
        if (Core::Util::String::starts_with(runtime->request()->target().to_string(), "/vortex_db")) {
            Maze::Element host(Maze::Type::Object);

			host.set("_id", Maze::Element({ "$oid" }, { Maze::Element("vortex_db_app") }));
			host.set("hostname", "unknown"); // TODO
			host.set("app_id", "vortex_db_app");
			
            runtime->host()->host_ref() = host;

            return true;
        }

        return false;
    }

}
