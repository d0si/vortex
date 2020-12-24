#include <Core/Modules/Plugin.h>

namespace Vortex::Core::Modules {

    bool Plugin::execute_before(RuntimeInterface* runtime, void* data) {
        return false;
    }

    bool Plugin::execute_after(RuntimeInterface* runtime, void* data) {
        return false;
    }


    void PluginManager::register_plugin(const std::shared_ptr<Plugin>& plugin) {
        switch (plugin->execute_point()) {
        case PluginExecutePoint::RUNTIME_INIT:
            _runtime_init.push_back(plugin);
            break;
        case PluginExecutePoint::RUNTIME_RUN:
            _runtime_run.push_back(plugin);
            break;
        case PluginExecutePoint::RUNTIME_EXIT:
            _runtime_exit.push_back(plugin);
            break;
        case PluginExecutePoint::HOST_INIT:
            _host_init.push_back(plugin);
            break;
        case PluginExecutePoint::APPLICATION_INIT:
            _application_init.push_back(plugin);
            break;
        case PluginExecutePoint::ROUTER_INIT:
            _router_init.push_back(plugin);
            break;
        case PluginExecutePoint::CONTROLLER_INIT:
            _controller_init.push_back(plugin);
            break;
        }
    }

    bool PluginManager::on_runtime_init_before(RuntimeInterface* runtime) {
        return execute_plugins_before(runtime, _runtime_init);
    }

    bool PluginManager::on_runtime_init_after(RuntimeInterface* runtime) {
        return execute_plugins_after(runtime, _runtime_init);
    }

    bool PluginManager::on_runtime_run_before(RuntimeInterface* runtime) {
        return execute_plugins_before(runtime, _runtime_run);
    }

    bool PluginManager::on_runtime_run_after(RuntimeInterface* runtime) {
        return execute_plugins_after(runtime, _runtime_run);
    }

    bool PluginManager::on_runtime_exit_before(RuntimeInterface* runtime) {
        return execute_plugins_before(runtime, _runtime_exit);
    }

    bool PluginManager::on_runtime_exit_after(RuntimeInterface* runtime) {
        return execute_plugins_after(runtime, _runtime_exit);
    }

    bool PluginManager::on_host_init_before(RuntimeInterface* runtime) {
        return execute_plugins_before(runtime, _host_init);
    }

    bool PluginManager::on_host_init_after(RuntimeInterface* runtime) {
        return execute_plugins_after(runtime, _host_init);
    }

    bool PluginManager::on_application_init_before(RuntimeInterface* runtime) {
        return execute_plugins_before(runtime, _application_init);
    }

    bool PluginManager::on_application_init_after(RuntimeInterface* runtime) {
        return execute_plugins_after(runtime, _application_init);
    }

    bool PluginManager::on_router_init_before(RuntimeInterface* runtime) {
        return execute_plugins_before(runtime, _router_init);
    }

    bool PluginManager::on_router_init_after(RuntimeInterface* runtime) {
        return execute_plugins_after(runtime, _router_init);
    }

    bool PluginManager::on_controller_init_before(RuntimeInterface* runtime, const std::string application_id, const std::string name, const std::string method, Maze::Element* controller_value) {
        ControllerInitData data{
            application_id,
            name,
            method,
            controller_value,
        };
        
        return execute_plugins_before(runtime, _controller_init, &data);
    }

    bool PluginManager::on_controller_init_after(RuntimeInterface* runtime, const std::string application_id, const std::string name, const std::string method, Maze::Element* controller_value) {
        ControllerInitData data{
            application_id,
            name,
            method,
            controller_value,
        };
        
        return execute_plugins_after(runtime, _controller_init, &data);
    }

    bool PluginManager::on_view_set_template_before(RuntimeInterface* runtime, const std::string& name, Maze::Element* template_value) {
        ViewSetTemplateData data{
            name,
            template_value,
        };

        return execute_plugins_before(runtime, _view_set_template, &data);
    }

    bool PluginManager::on_view_set_template_after(RuntimeInterface* runtime, const std::string& name, Maze::Element* template_value) {
        ViewSetTemplateData data{
            name,
            template_value,
        };

        return execute_plugins_after(runtime, _view_set_template, &data);
    }

    bool PluginManager::on_view_set_page_before(RuntimeInterface* runtime, const std::string& name, Maze::Element* page_value) {
        ViewSetPageData data{
            name,
            page_value,
        };
        
        return execute_plugins_before(runtime, _view_set_page, &data);
    }

    bool PluginManager::on_view_set_page_after(RuntimeInterface* runtime, const std::string& name, Maze::Element* page_value) {
        ViewSetPageData data{
            name,
            page_value,
        };
        
        return execute_plugins_after(runtime, _view_set_page, &data);
    }

    PluginManager* PluginManager::instance() {
        return _s_instance;
    }

    bool PluginManager::execute_plugins_before(RuntimeInterface* runtime, const std::vector<std::shared_ptr<Plugin>> plugins, void* data) {
        for (const auto& plugin : plugins) {
            if (plugin->execute_before(runtime, data))
                return true;
        }

        return false;
    }

    bool PluginManager::execute_plugins_after(RuntimeInterface* runtime, const std::vector<std::shared_ptr<Plugin>> plugins, void* data) {
        for (const auto& plugin : plugins) {
            if (plugin->execute_after(runtime, data))
                return true;
        }

        return false;
    }

    PluginManager* PluginManager::_s_instance = new PluginManager();

}
