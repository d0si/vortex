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

    bool DbApplicationPlugin::execute_before(Vortex::Core::RuntimeInterface* runtime) {
        if (runtime->host()->application_id() == "vortex_db_app") {
            Maze::Element application(Maze::Type::Object);
            Maze::Element url_schemes(Maze::Type::Array);
            url_schemes << Maze::Element() << Maze::Element(
                { "default_value", "type" },
                { Maze::Element("db"), Maze::Element("controller") }
            ) << Maze::Element(
                { "default_value", "type" },
                { Maze::Element("list"), Maze::Element("controller") }
            ) << Maze::Element("args");

            application.set("_id", Maze::Element({ "$oid" }, { Maze::Element("vortex_db_app") }));
            application.set("title", "Vortex DB");
            application.set("config", Maze::Element(
                { "router" },
                { Maze::Element(
                    {"url_schemes"},
                    {url_schemes})
                }));
            application.set("script", "view.set_template('vortex/db')");

            runtime->application()->application_ref() = application;

            return true;
        }

        return false;
    }

}
