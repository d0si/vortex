#include "DbViewTemplatePlugin.h"
#include <Core/Interfaces.h>
#include <Core/Util/String.h>

const std::string template_val = R"(
{{
var site_title = application.get_title();
}}<!DOCTYPE html>
<html style="height: auto; min-height: 100%;" lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="description" content="">
  <meta name="author" content="">
  <meta name="keyword" content="">
  <link rel="icon" href="/public/img/favicon.ico">
  
  <title>{= site_title =}</title>

  <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">

  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.2.0/css/all.css" integrity="sha384-hWVjflwFxL6sNzntih27bfxkr27PmbbK/iSvJ+a4+0owXq79v+lsFkW54bOGbiDQ" crossorigin="anonymous">
  <script src="https://code.jquery.com/jquery-3.3.1.min.js" integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8=" crossorigin="anonymous"></script>

  <style>
  .page-wrapper {
    width: 99%;
    max-width: 1300px;
    margin: 16px auto;
  }
  </style>
</head>
<body>
  <nav class="navbar navbar-dark bg-primary">
    <a class="navbar-brand" href="/">{= application.get_title() =}</a>
  </nav>
  
  <div class="page-wrapper">
    <div class="p-2">{= view.parse_page() =}</div>
  </div>

  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
  <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
</body>
</html>
)";


namespace Vortex::App::Db::Plugins {

    const std::string DbViewTemplatePlugin::s_plugin_name = "DbViewTemplatePlugin";

    const std::string DbViewTemplatePlugin::plugin_name() const {
        return s_plugin_name;
    }

    Vortex::Core::Modules::PluginExecutePoint DbViewTemplatePlugin::execute_point() {
        return Vortex::Core::Modules::PluginExecutePoint::VIEW_SET_TEMPLATE;
    }

    bool DbViewTemplatePlugin::execute_before(Vortex::Core::RuntimeInterface* runtime, void* data) {
        if (runtime->host()->application_id() == "vortex_db_app") {
            Core::Modules::ViewSetTemplateData* set_data = (Core::Modules::ViewSetTemplateData*)data;
            if (set_data->name == "vortex/db") {
                Maze::Element template_value(Maze::Type::Object);

                template_value.set("contents", template_val);

                set_data->template_value->copy_from_element(template_value);

                return true;
            }
        }

        return false;
    }

}
