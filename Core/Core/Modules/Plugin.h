#pragma once

#include <string>
#include <memory>
#include <vector>
#include <Core/DLLSupport.h>
#include <Maze/Maze.hpp>

namespace Vortex::Core {
    class RuntimeInterface;
}

namespace Vortex::Core::Modules {

    enum class PluginExecutePoint {
        RUNTIME_INIT,
        RUNTIME_RUN,
        RUNTIME_EXIT,
        HOST_INIT,
        APPLICATION_INIT,
        ROUTER_INIT,
        CONTROLLER_INIT,
        VIEW_SET_TEMPLATE,
        VIEW_SET_PAGE,
    };


    struct ControllerInitData {
        const std::string application_id;
        const std::string name;
        const std::string method;
        Maze::Element* controller_value;
    };

    struct ViewSetTemplateData {
        const std::string name;
        Maze::Element* template_value;
    };

    struct ViewSetPageData {
        const std::string name;
        Maze::Element* page_value;
    };


    class Plugin {
    public:
        VORTEX_CORE_API virtual ~Plugin() = default;

        VORTEX_CORE_API virtual const std::string plugin_name() const = 0;
        VORTEX_CORE_API virtual PluginExecutePoint execute_point() = 0;

        VORTEX_CORE_API virtual bool execute_before(RuntimeInterface*, void* data = nullptr);
        VORTEX_CORE_API virtual bool execute_after(RuntimeInterface*, void* data = nullptr);
    };


    class PluginManager {
    public:
        VORTEX_CORE_API void register_plugin(const std::shared_ptr<Plugin>& plugin);

        VORTEX_CORE_API bool on_runtime_init_before(RuntimeInterface*);
        VORTEX_CORE_API bool on_runtime_init_after(RuntimeInterface*);
        VORTEX_CORE_API bool on_runtime_run_before(RuntimeInterface*);
        VORTEX_CORE_API bool on_runtime_run_after(RuntimeInterface*);
        VORTEX_CORE_API bool on_runtime_exit_before(RuntimeInterface*);
        VORTEX_CORE_API bool on_runtime_exit_after(RuntimeInterface*);

        VORTEX_CORE_API bool on_host_init_before(RuntimeInterface*);
        VORTEX_CORE_API bool on_host_init_after(RuntimeInterface*);

        VORTEX_CORE_API bool on_application_init_before(RuntimeInterface*);
        VORTEX_CORE_API bool on_application_init_after(RuntimeInterface*);

        VORTEX_CORE_API bool on_router_init_before(RuntimeInterface*);
        VORTEX_CORE_API bool on_router_init_after(RuntimeInterface*);

        VORTEX_CORE_API bool on_controller_init_before(RuntimeInterface*, const std::string application_id, const std::string name, const std::string method, Maze::Element* controller_value);
        VORTEX_CORE_API bool on_controller_init_after(RuntimeInterface*, const std::string application_id, const std::string name, const std::string method, Maze::Element* controller_value);

        VORTEX_CORE_API bool on_view_set_template_before(RuntimeInterface*, const std::string& name, Maze::Element* template_value);
        VORTEX_CORE_API bool on_view_set_template_after(RuntimeInterface*, const std::string& name, Maze::Element* template_value);
        VORTEX_CORE_API bool on_view_set_page_before(RuntimeInterface*, const std::string& name, Maze::Element* page_value);
        VORTEX_CORE_API bool on_view_set_page_after(RuntimeInterface*, const std::string& name, Maze::Element* page_value);

        VORTEX_CORE_API static PluginManager* instance();

    protected:
        std::vector<std::shared_ptr<Plugin>> _runtime_init;
        std::vector<std::shared_ptr<Plugin>> _runtime_run;
        std::vector<std::shared_ptr<Plugin>> _runtime_exit;
        std::vector<std::shared_ptr<Plugin>> _host_init;
        std::vector<std::shared_ptr<Plugin>> _application_init;
        std::vector<std::shared_ptr<Plugin>> _router_init;
        std::vector<std::shared_ptr<Plugin>> _controller_init;
        std::vector<std::shared_ptr<Plugin>> _view_set_page;
        std::vector<std::shared_ptr<Plugin>> _view_set_template;

    private:
        static PluginManager* _s_instance;

        bool execute_plugins_before(RuntimeInterface* runtime, const std::vector<std::shared_ptr<Plugin>> plugins, void* data = nullptr);
        bool execute_plugins_after(RuntimeInterface* runtime, const std::vector<std::shared_ptr<Plugin>> plugins, void* data = nullptr);
    };

}  // namespace Vortex::Core::Modules
