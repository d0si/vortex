#include "DbControllerPlugin.h"
#include <Core/Interfaces.h>
#include <Core/Util/String.h>

namespace Vortex::App::Db::Plugins {

    const std::string DbControllerPlugin::s_plugin_name = "DbControllerPlugin";

    const std::string DbControllerPlugin::plugin_name() const {
        return s_plugin_name;
    }

    Vortex::Core::Modules::PluginExecutePoint DbControllerPlugin::execute_point() {
        return Vortex::Core::Modules::PluginExecutePoint::CONTROLLER_INIT;
    }

    bool DbControllerPlugin::execute_before(Vortex::Core::RuntimeInterface* runtime, void* data) {
        if (runtime->host()->application_id() == "vortex_db_app") {
            Core::Modules::ControllerInitData* init_data = (Core::Modules::ControllerInitData*)data;
            if (init_data->name == "col/view" && init_data->method == "GET") {
                Maze::Element controller_value(Maze::Type::Object);

                controller_value.set("name", "col/view");
                controller_value.set("method", "GET");
                controller_value.set("script", R"(var router_args = router.get_args();

if (router_args.length != 2) {
    view.set_page('invalid_request');
} else {
    view.set_page('item_list');
    var db_name = router_args[0];
    var collection_name = router_args[1];
}
view.set_page('invalid_request');
)");

                init_data->controller_value->copy_from_element(controller_value);

                return true;
            }
        }

        return false;
    }

}
