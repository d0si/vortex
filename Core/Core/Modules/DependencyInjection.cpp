#include <Core/Modules/DependencyInjection.hpp>
#include <Core/Exceptions/VortexException.hpp>

namespace Vortex::Core::Modules {

    DependencyInjector::DependencyInjector(std::shared_ptr<DependencyInjector> parent)
        : _parent(parent) {}

    std::shared_ptr<DependencyInjector> DependencyInjector::di_scope() {
        return shared_from_this();
    }

    DependencyInjector DependencyInjector::di_scope_temp() {
        return DependencyInjector(shared_from_this());
    }

    std::shared_ptr<DependencyInjector> DependencyInjector::di_global() {
        return s_global;
    }



    void DependencyInjector::install(ApplicationResolverActivator activator) {
        _application_resolver_activator = activator;
    }

    std::shared_ptr<Applications::IApplicationResolver> DependencyInjector::activate_application_resolver(
        const std::shared_ptr<Applications::string_body_request>& request,
        const std::shared_ptr<Applications::string_body_response>& response,
        const Maze::Element& config) {
        return activate_application_resolver(shared_from_this(), request, response, config);
    }

    std::shared_ptr<Applications::IApplicationResolver> DependencyInjector::activate_application_resolver(
        const std::shared_ptr<DependencyInjector>& di,
        const std::shared_ptr<Applications::string_body_request>& request,
        const std::shared_ptr<Applications::string_body_response>& response,
        const Maze::Element& config) {
        if (_application_resolver_activator)
            return _application_resolver_activator(di, request, response, config);

        if (_parent)
            return _parent->activate_application_resolver(di, request, response, config);

        throw Exceptions::VortexException("Dependency injection failed", "Unable to activate application resolver - no suitable activator installed");
    }



    void DependencyInjector::install(ApplicationRuntimeActivator activator) {
        _application_runtime_activator = activator;
    }

    std::shared_ptr<Applications::IApplicationRuntime> DependencyInjector::activate_application_runtime(
        const std::shared_ptr<Applications::string_body_request>& request,
        const std::shared_ptr<Applications::string_body_response>& response,
        const Maze::Element& host_info,
        const Maze::Element& app_info,
        const Maze::Element& config) {
        return activate_application_runtime(shared_from_this(), request, response, host_info, app_info, config);
    }

    std::shared_ptr<Applications::IApplicationRuntime> DependencyInjector::activate_application_runtime(
        const std::shared_ptr<DependencyInjector>& di,
        const std::shared_ptr<Applications::string_body_request>& request,
        const std::shared_ptr<Applications::string_body_response>& response,
        const Maze::Element& host_info,
        const Maze::Element& app_info,
        const Maze::Element& config) {
        if (_application_runtime_activator) {
            _application_runtime_instance = _application_runtime_activator(di, request, response, host_info, app_info, config);

            return _application_runtime_instance;
        }

        if (_parent)
            return _parent->activate_application_runtime(di, request, response, host_info, app_info, config);

        throw Exceptions::VortexException("Dependency injection failed", "Unable to activate application runtime - no suitable activator installed");
    }

    std::shared_ptr<Applications::IApplicationRuntime> DependencyInjector::application_runtime() {
        if (_application_runtime_instance)
            return _application_runtime_instance;

        if (_parent)
            return _parent->application_runtime();

        return nullptr;
    }



    void DependencyInjector::install(RouterActivator activator) {
        _router_activator = activator;
    }

    std::shared_ptr<Applications::IRouter> DependencyInjector::activate_router(
        const std::shared_ptr<Applications::IApplicationRuntime>& runtime) {
        return activate_router(shared_from_this(), runtime);
    }

    std::shared_ptr<Applications::IRouter> DependencyInjector::activate_router(
        const std::shared_ptr<DependencyInjector>& di,
        const std::shared_ptr<Applications::IApplicationRuntime>& runtime) {
        if (_router_activator) {
            _router_instance = _router_activator(di, runtime);

            return _router_instance;
        }

        if (_parent)
            return _parent->activate_router(di, runtime);

        throw Exceptions::VortexException("Dependency injection failed", "Unable to activate router - no suitable activator installed");
    }

    std::shared_ptr<Applications::IRouter> DependencyInjector::router() {
        if (_router_instance)
            return _router_instance;

        if (_parent)
            return _parent->router();

        return nullptr;
    }



    ModuleLoader* DependencyInjector::module_loader() {
        return ModuleLoader::loader();
    }

    std::shared_ptr<DependencyInjector> DependencyInjector::s_global = std::make_shared<DependencyInjector>();

}
