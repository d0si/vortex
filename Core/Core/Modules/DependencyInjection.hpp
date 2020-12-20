#pragma once

#include <memory>
#include <Core/DLLSupport.hpp>
#include <Core/Modules/ModuleLoader.hpp>
#include <Core/Applications/Application.hpp>
#include <Core/Applications/Routing.hpp>

namespace Vortex::Core::Modules {

    // TODO: Add some way to mark scope type so dependencies can specify a barrier to where search for dependency can go, e.g. enum with Global, Session, Application...
    // TODO: Applications should use a struct with identifier parameter so they can be properly resolved.
    class DependencyInjector : public std::enable_shared_from_this<DependencyInjector> {
    public:
        VORTEX_CORE_API DependencyInjector() = default;
        VORTEX_CORE_API DependencyInjector(std::shared_ptr<DependencyInjector> parent);
        VORTEX_CORE_API virtual ~DependencyInjector() = default;

        VORTEX_CORE_API virtual std::shared_ptr<DependencyInjector> di_scope();
        VORTEX_CORE_API virtual DependencyInjector di_scope_temp();
        VORTEX_CORE_API static std::shared_ptr<DependencyInjector> di_global();


        typedef std::shared_ptr<Applications::IApplicationResolver>(*ApplicationResolverActivator)(
            const std::shared_ptr<DependencyInjector>& di,
            const std::shared_ptr<Applications::string_body_request>& request,
            const std::shared_ptr<Applications::string_body_response>& response,
            const Maze::Element& config);
        VORTEX_CORE_API virtual void install(ApplicationResolverActivator activator);
        VORTEX_CORE_API virtual std::shared_ptr<Applications::IApplicationResolver> activate_application_resolver(
            const std::shared_ptr<Applications::string_body_request>& request,
            const std::shared_ptr<Applications::string_body_response>& response,
            const Maze::Element& config);
        VORTEX_CORE_API virtual std::shared_ptr<Applications::IApplicationResolver> activate_application_resolver(
            const std::shared_ptr<DependencyInjector>& di,
            const std::shared_ptr<Applications::string_body_request>& request,
            const std::shared_ptr<Applications::string_body_response>& response,
            const Maze::Element& config);


        typedef std::shared_ptr<Applications::IApplicationRuntime>(*ApplicationRuntimeActivator)(
            const std::shared_ptr<DependencyInjector>& di,
            const std::shared_ptr<Applications::string_body_request>& request,
            const std::shared_ptr<Applications::string_body_response>& response,
            const Maze::Element& host_info,
            const Maze::Element& app_info,
            const Maze::Element& config);
        VORTEX_CORE_API virtual void install(ApplicationRuntimeActivator activator);
        VORTEX_CORE_API virtual std::shared_ptr<Applications::IApplicationRuntime> activate_application_runtime(
            const std::shared_ptr<Applications::string_body_request>& request,
            const std::shared_ptr<Applications::string_body_response>& response,
            const Maze::Element& host_info,
            const Maze::Element& app_info,
            const Maze::Element& config);
        VORTEX_CORE_API virtual std::shared_ptr<Applications::IApplicationRuntime> activate_application_runtime(
            const std::shared_ptr<DependencyInjector>& di,
            const std::shared_ptr<Applications::string_body_request>& request,
            const std::shared_ptr<Applications::string_body_response>& response,
            const Maze::Element& host_info,
            const Maze::Element& app_info,
            const Maze::Element& config);
        VORTEX_CORE_API virtual std::shared_ptr<Applications::IApplicationRuntime> application_runtime();


        typedef std::shared_ptr<Applications::IRouter>(*RouterActivator)(
            const std::shared_ptr<DependencyInjector>& di,
            const std::shared_ptr<Applications::IApplicationRuntime>& runtime);
        VORTEX_CORE_API virtual void install(RouterActivator activator);
        VORTEX_CORE_API virtual std::shared_ptr<Applications::IRouter> activate_router(
            const std::shared_ptr<Applications::IApplicationRuntime>& runtime);
        VORTEX_CORE_API virtual std::shared_ptr<Applications::IRouter> activate_router(
            const std::shared_ptr<DependencyInjector>& di,
            const std::shared_ptr<Applications::IApplicationRuntime>& runtime);
        VORTEX_CORE_API virtual std::shared_ptr<Applications::IRouter> router();


        VORTEX_CORE_API static ModuleLoader* module_loader();

    private:
        std::shared_ptr<DependencyInjector> _parent = nullptr;

        ApplicationResolverActivator _application_resolver_activator;

        ApplicationRuntimeActivator _application_runtime_activator;
        std::shared_ptr<Applications::IApplicationRuntime> _application_runtime_instance;

        RouterActivator _router_activator;
        std::shared_ptr<Applications::IRouter> _router_instance;

        static std::shared_ptr<DependencyInjector> s_global;
    };

}  // namespace Vortex::Core::Modules
