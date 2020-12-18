#include <Core/Modules/DependencyInjection.hpp>
#include <Core/Exceptions/VortexException.hpp>

#define ADD_DEPENDENCY_INSTALLER_IMPL(field_name, type_prefix)                                                                      \
    VORTEX_CORE_API void DependencyInjector::install(type_prefix##Activator activator) { _##field_name##_activator = activator; }

#define ADD_DEPENDENCY_ACTIVATOR_DI_CTOR_IMPL(field_name, type_prefix)                                                                                          \
    VORTEX_CORE_API const std::shared_ptr<type_prefix##Interface>& DependencyInjector::activate_##field_name(const std::shared_ptr<DependencyInjector>& di) {   \
        if (_##field_name##_activator) {                                                                                                                        \
            _##field_name##_instance = _##field_name##_activator(di);                                                                                           \
                                                                                                                                                                \
            return _##field_name##_instance;                                                                                                                    \
        }                                                                                                                                                       \
                                                                                                                                                                \
        if (_parent) return _parent->activate_##field_name##(di);                                                                                               \
                                                                                                                                                                \
        throw Exceptions::VortexException("Unable to activate ##field_name##", "Dependency injection resolve failed. No applicable activator installed.");      \
    }

#define ADD_DEPENDENCY_GETTER_IMPL(field_name, type_prefix)                                                                                 \
    VORTEX_CORE_API const std::shared_ptr<type_prefix##Interface>& DependencyInjector::field_name() { return _##field_name##_instance; }

#define ADD_DEPENDENCY_DI_CTOR_IMPLS(field_name, type_prefix)       \
    ADD_DEPENDENCY_INSTALLER_IMPL(field_name, type_prefix)          \
    ADD_DEPENDENCY_ACTIVATOR_DI_CTOR_IMPL(field_name, type_prefix)  \
    ADD_DEPENDENCY_GETTER_IMPL(field_name, type_prefix)


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

    std::shared_ptr<Applications::IApplicationResolver> DependencyInjector::activate_application_resolver() {
        if (_application_resolver_activator)
            return _application_resolver_activator();

        if (_parent)
            return _parent->activate_application_resolver();

        throw Exceptions::VortexException("Dependency injection failed", "Unable to activate application resolver - no suitable activator installed");
    }

    void DependencyInjector::install(ApplicationRuntimeActivator activator) {
        _application_runtime_activator = activator;
    }

    std::shared_ptr<Applications::IApplicationRuntime> DependencyInjector::activate_application_runtime() {
        if (_application_runtime_activator) {
            _application_runtime_instance = _application_runtime_activator();

            return _application_runtime_instance;
        }

        if (_parent)
            return _parent->activate_application_runtime();

        throw Exceptions::VortexException("Dependency injection failed", "Unable to activate application runtime - no suitable activator installed");
    }

    std::shared_ptr<Applications::IApplicationRuntime> DependencyInjector::application_runtime() {
        if (_application_runtime_instance)
            return _application_runtime_instance;

        if (_parent)
            return _parent->application_runtime();

        return nullptr;
    }


    /*void DependencyInjector::install(RuntimeActivator activator) {
        _runtime_activator = activator;
    }
    ADD_DEPENDENCY_INSTALLER_IMPL(runtime, Runtime)
        const std::shared_ptr<RuntimeInterface>& DependencyInjector::activate_runtime(const std::shared_ptr<DependencyInjector>& di, const Maze::Element& config, std::string client_ip, boost::beast::http::request<boost::beast::http::string_body>* request, boost::beast::http::response<boost::beast::http::string_body>* response) {
        if (_runtime_activator) {
            _runtime_instance = _runtime_activator(di, config, client_ip, request, response);

            return _runtime_instance;
        }

        if (_parent)
            return _parent->activate_runtime(di, config, client_ip, request, response);

        throw Exceptions::VortexException("Unable to activate runtime", "Dependency injection resolve failed. No applicable activator installed.");
    }
    ADD_DEPENDENCY_GETTER_IMPL(runtime, Runtime);

    ADD_DEPENDENCY_DI_CTOR_IMPLS(host, Host);
    ADD_DEPENDENCY_DI_CTOR_IMPLS(application, Application);
    ADD_DEPENDENCY_DI_CTOR_IMPLS(router, Router);
    ADD_DEPENDENCY_DI_CTOR_IMPLS(controller, Controller);
    ADD_DEPENDENCY_DI_CTOR_IMPLS(view, View);
    ADD_DEPENDENCY_DI_CTOR_IMPLS(script, Script);
    */

    ModuleLoader* DependencyInjector::module_loader() {
        return ModuleLoader::loader();
    }

    std::shared_ptr<DependencyInjector> DependencyInjector::s_global = std::make_shared<DependencyInjector>();

}
