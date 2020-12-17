#include <Core/Modules/DependencyInjection.h>
#include <Core/Exceptions/VortexException.h>

#define ADD_DEPENDENCY_FUNCS(field_name, type_prefix, activate_arg,...)                                             \
    void DependencyInjector::install(type_prefix##Activator activator) { _##field_name##_activator = activator; }   \
    const std::shared_ptr<type_prefix##Interface>& DependencyInjector::activate_##field_name(__VA_ARGS__) {         \
        if (_##field_name##_activator) {                                                                            \
            _##field_name##_instance = _##field_name##_activator(activate_arg);                                     \
                                                                                                                    \
            return _##field_name##_instance;                                                                        \
        }                                                                                                           \
                                                                                                                    \
        if (_parent) return _parent->activate_##field_name##(activate_arg);                                         \
                                                                                                                    \
        throw Exceptions::VortexException("Unable to activate ##field_name##", "Dependency injection resolve failed. No applicable activator installed."); \
    }                                                                                                               \
    const std::shared_ptr<type_prefix##Interface>& DependencyInjector::field_name() {                               \
        return _##field_name##_instance;                                                                            \
    }

namespace Vortex::Core::Modules {

    DependencyInjector::DependencyInjector(DependencyInjector* parent)
        : _parent(parent) {
        if (_parent != nullptr)
            _parent->add_ref();
    }

    DependencyInjector::~DependencyInjector() {
        if (_parent != nullptr) {
            _parent->del_ref();
        }
    }

    DependencyInjector* DependencyInjector::di_scope() {
        return new DependencyInjector(this);
    }

    DependencyInjector DependencyInjector::di_scope_temp() {
        return DependencyInjector(this);
    }

    DependencyInjector* DependencyInjector::di_global() {
        return &s_global;
    }

    void DependencyInjector::install(RuntimeActivator activator) {
        _runtime_activator = activator;
    }

    const std::shared_ptr<RuntimeInterface>& DependencyInjector::activate_runtime(const Maze::Element& config, std::string client_ip, boost::beast::http::request<boost::beast::http::string_body>* request, boost::beast::http::response<boost::beast::http::string_body>* response) {
        if (_runtime_activator) {
            _runtime_instance = _runtime_activator(config, client_ip, request, response);

            return _runtime_instance;
        }

        if (_parent)
            return _parent->activate_runtime(config, client_ip, request, response);

        throw Exceptions::VortexException("Unable to activate runtime", "Dependency injection resolve failed. No applicable activator installed.");
    }

    const std::shared_ptr<RuntimeInterface>& DependencyInjector::runtime() {
        return _runtime_instance;
    }

    ADD_DEPENDENCY_FUNCS(host, Host, runtime, const std::shared_ptr<RuntimeInterface> runtime);
    ADD_DEPENDENCY_FUNCS(application, Application, runtime, const std::shared_ptr<RuntimeInterface> runtime);
    ADD_DEPENDENCY_FUNCS(router, Router, runtime, const std::shared_ptr<RuntimeInterface> runtime);
    ADD_DEPENDENCY_FUNCS(controller, Controller, runtime, const std::shared_ptr<RuntimeInterface> runtime);
    ADD_DEPENDENCY_FUNCS(view, View, runtime, const std::shared_ptr<RuntimeInterface> runtime);
    ADD_DEPENDENCY_FUNCS(script, Script, runtime, const std::shared_ptr<RuntimeInterface> runtime);

    ModuleLoader* DependencyInjector::module_loader() {
        return ModuleLoader::loader();
    }

    void DependencyInjector::add_ref() {
        ++_refs_count;
    }

    void DependencyInjector::del_ref() {
        --_refs_count;

        if (_refs_count <= 0) {
            delete this;
        }
    }

    DependencyInjector DependencyInjector::s_global;

}
