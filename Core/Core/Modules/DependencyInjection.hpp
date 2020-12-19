#pragma once

#include <memory>
#include <Core/DLLSupport.hpp>
#include <Core/Modules/ModuleLoader.hpp>
#include <Core/Applications/Application.hpp>

#define ADD_DEPENDENCY_TYPEDEF(type_prefix, ...) typedef std::shared_ptr<I##type_prefix>(*type_prefix##Activator)(__VA_ARGS__)
#define ADD_DEPENDENCY_INSTALLER(type_prefix) VORTEX_CORE_API void install(type_prefix##Activator activator)
#define ADD_DEPENDENCY_ACTIVATOR(field_name, type_prefix, ...) VORTEX_CORE_API const std::shared_ptr<I##type_prefix>& activate_##field_name(__VA_ARGS__)
#define ADD_DEPENDENCY_GETTER(field_name, type_prefix) VORTEX_CORE_API const std::shared_ptr<I##type_prefix>& field_name()

#define ADD_DEPENDENCY_PUBLIC_FUNCS(field_name, type_prefix, ...)   \
    ADD_DEPENDENCY_TYPEDEF(type_prefix, __VA_ARGS__);               \
    ADD_DEPENDENCY_INSTALLER(type_prefix);                          \
    ADD_DEPENDENCY_ACTIVATOR(field_name, type_prefix, __VA_ARGS__); \
    ADD_DEPENDENCY_GETTER(field_name, type_prefix)

#define ADD_DEPENDENCY_WITH_DI_CTOR(field_name, type_prefix) \
    ADD_DEPENDENCY_PUBLIC_FUNCS(field_name, type_prefix, const std::shared_ptr<DependencyInjector>& di)

#define ADD_DEPENDENCY_PRIVATE_FIELDS(field_name, type_prefix)          \
    type_prefix##Activator _##field_name##_activator;                   \
    std::shared_ptr<I##type_prefix> _##field_name##_instance


namespace Vortex::Core::Modules {

    class DependencyInjector : public std::enable_shared_from_this<DependencyInjector> {
    public:
        VORTEX_CORE_API DependencyInjector() = default;
        VORTEX_CORE_API DependencyInjector(std::shared_ptr<DependencyInjector> parent);
        VORTEX_CORE_API virtual ~DependencyInjector() = default;

        VORTEX_CORE_API virtual std::shared_ptr<DependencyInjector> di_scope();
        VORTEX_CORE_API virtual DependencyInjector di_scope_temp();
        VORTEX_CORE_API static std::shared_ptr<DependencyInjector> di_global();

        /*ADD_DEPENDENCY_PUBLIC_FUNCS(runtime, Runtime,
            const std::shared_ptr<DependencyInjector>&,
            const Maze::Element& config,
            std::string client_ip,
            boost::beast::http::request<boost::beast::http::string_body>* request,
            boost::beast::http::response<boost::beast::http::string_body>* response);*/
        /*ADD_DEPENDENCY_WITH_DI_CTOR(host, Host);
        ADD_DEPENDENCY_WITH_DI_CTOR(application, Application);
        ADD_DEPENDENCY_WITH_DI_CTOR(router, Router);
        ADD_DEPENDENCY_WITH_DI_CTOR(controller, Controller);
        ADD_DEPENDENCY_WITH_DI_CTOR(view, View);
        ADD_DEPENDENCY_WITH_DI_CTOR(script, Script);*/



        typedef std::shared_ptr<Applications::IApplicationResolver>(*ApplicationResolverActivator)(
            const std::shared_ptr<DependencyInjector>& di,
            const std::shared_ptr<Applications::string_body_request>& request,
            const std::shared_ptr<Applications::string_body_response>& response);
        VORTEX_CORE_API virtual void install(ApplicationResolverActivator activator);
        VORTEX_CORE_API virtual std::shared_ptr<Applications::IApplicationResolver> activate_application_resolver(
            const std::shared_ptr<Applications::string_body_request>& request,
            const std::shared_ptr<Applications::string_body_response>& response);
        VORTEX_CORE_API virtual std::shared_ptr<Applications::IApplicationResolver> activate_application_resolver(
            const std::shared_ptr<DependencyInjector>& di,
            const std::shared_ptr<Applications::string_body_request>& request,
            const std::shared_ptr<Applications::string_body_response>& response);

        typedef std::shared_ptr<Applications::IApplicationRuntime>(*ApplicationRuntimeActivator)();
        VORTEX_CORE_API virtual void install(ApplicationRuntimeActivator activator);
        VORTEX_CORE_API virtual std::shared_ptr<Applications::IApplicationRuntime> activate_application_runtime();
        VORTEX_CORE_API virtual std::shared_ptr<Applications::IApplicationRuntime> application_runtime();

        VORTEX_CORE_API static ModuleLoader* module_loader();

    private:
        std::shared_ptr<DependencyInjector> _parent = nullptr;

        ApplicationResolverActivator _application_resolver_activator;

        ApplicationRuntimeActivator _application_runtime_activator;
        std::shared_ptr<Applications::IApplicationRuntime> _application_runtime_instance;

        //ADD_DEPENDENCY_PRIVATE_FIELDS(runtime, Runtime);
        /*ADD_DEPENDENCY_PRIVATE_FIELDS(host, Host);
        ADD_DEPENDENCY_PRIVATE_FIELDS(application, Application);
        ADD_DEPENDENCY_PRIVATE_FIELDS(router, Router);
        ADD_DEPENDENCY_PRIVATE_FIELDS(controller, Controller);
        ADD_DEPENDENCY_PRIVATE_FIELDS(view, View);
        ADD_DEPENDENCY_PRIVATE_FIELDS(script, Script);*/

        static std::shared_ptr<DependencyInjector> s_global;
    };

}  // namespace Vortex::Core::Modules
