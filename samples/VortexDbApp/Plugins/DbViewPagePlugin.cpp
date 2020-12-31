#include "DbViewPagePlugin.h"
#include <Core/Interfaces.h>
#include <Core/Util/String.h>

namespace Vortex::App::Db::Plugins {

    const std::string DbViewPagePlugin::s_plugin_name = "DbViewPagePlugin";

    const std::string DbViewPagePlugin::plugin_name() const {
        return s_plugin_name;
    }

    Vortex::Core::Modules::PluginExecutePoint DbViewPagePlugin::execute_point() {
        return Vortex::Core::Modules::PluginExecutePoint::VIEW_SET_TEMPLATE;
    }

    bool DbViewPagePlugin::execute_before(Vortex::Core::RuntimeInterface* runtime, void* data) {
        if (runtime->host()->application_id() == "vortex_db_app") {
            /*Core::Modules::ViewSetPageData* set_data = (Core::Modules::ViewSetPageData*)data;
            if (set_data->name == "") {

            }

            Maze::Element host(Maze::Type::Object);

            host.set("_id", Maze::Element({ "$oid" }, { Maze::Element("vortex_db_app") }));
            host.set("hostname", runtime->router()->hostname());
            host.set("app_id", "vortex_db_app");

            runtime->host()->host_ref() = host;

            return true;*/
        }

        return false;
    }

}
