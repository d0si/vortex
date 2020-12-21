#pragma once

#include <memory>
#include <Core/DLLSupport.h>
#include <Core/Interfaces.h>
#include <Core/Modules/ModuleLoader.h>

#define ADD_DEPENDENCY(field_name, type_prefix, ...)                                                    \
    typedef std::shared_ptr<type_prefix##Interface>(*type_prefix##Activator)(__VA_ARGS__);              \
    VORTEX_CORE_API void install(type_prefix##Activator activator);                                     \
    VORTEX_CORE_API const std::shared_ptr<type_prefix##Interface>& activate_##field_name(__VA_ARGS__);  \
    VORTEX_CORE_API const std::shared_ptr<type_prefix##Interface>& field_name()

#define ADD_DEPENDENCY_PRIVATE_FIELDS(field_name, type_prefix)                  \
    type_prefix##Activator _##field_name##_activator = nullptr;                 \
    std::shared_ptr<type_prefix##Interface> _##field_name##_instance = nullptr


namespace Vortex::Core::Modules {

    class DependencyInjector {
    public:
        VORTEX_CORE_API DependencyInjector() = default;
        VORTEX_CORE_API DependencyInjector(DependencyInjector* parent);
        VORTEX_CORE_API ~DependencyInjector();

        VORTEX_CORE_API DependencyInjector* di_scope();
        VORTEX_CORE_API DependencyInjector di_scope_temp();
        VORTEX_CORE_API static DependencyInjector* di_global();

        ADD_DEPENDENCY(runtime, Runtime, const Maze::Element& config, std::string client_ip, boost::beast::http::request<boost::beast::http::string_body>* request, boost::beast::http::response<boost::beast::http::string_body>* response);
        ADD_DEPENDENCY(host, Host, const std::shared_ptr<RuntimeInterface> runtime);
        ADD_DEPENDENCY(application, Application, const std::shared_ptr<RuntimeInterface> runtime);
        ADD_DEPENDENCY(router, Router, const std::shared_ptr<RuntimeInterface> runtime);
        ADD_DEPENDENCY(controller, Controller, const std::shared_ptr<RuntimeInterface> runtime);
        ADD_DEPENDENCY(view, View, const std::shared_ptr<RuntimeInterface> runtime);
        ADD_DEPENDENCY(script, Script, const std::shared_ptr<RuntimeInterface> runtime);

        VORTEX_CORE_API static ModuleLoader* module_loader();

        VORTEX_CORE_API void add_ref();
        VORTEX_CORE_API void del_ref();

    private:
        DependencyInjector* _parent = nullptr;
        int _refs_count = 0;

        ADD_DEPENDENCY_PRIVATE_FIELDS(runtime, Runtime);
        ADD_DEPENDENCY_PRIVATE_FIELDS(host, Host);
        ADD_DEPENDENCY_PRIVATE_FIELDS(application, Application);
        ADD_DEPENDENCY_PRIVATE_FIELDS(router, Router);
        ADD_DEPENDENCY_PRIVATE_FIELDS(controller, Controller);
        ADD_DEPENDENCY_PRIVATE_FIELDS(view, View);
        ADD_DEPENDENCY_PRIVATE_FIELDS(script, Script);

        static DependencyInjector s_global;
    };

}  // namespace Vortex::Core::Modules
