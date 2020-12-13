#include <Core/Modules/DependencyInjection.h>
#include <Core/Exceptions/VortexException.h>

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

        if (_framework_instance)
            delete _framework_instance;
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

    void DependencyInjector::install(FrameworkInterface* (*framework_activate)(const Maze::Element& config, std::string client_ip, boost::beast::http::request<boost::beast::http::string_body>* request, boost::beast::http::response<boost::beast::http::string_body>* response)) {
        _framework_activator = framework_activate;
    }

    FrameworkInterface* DependencyInjector::activate_framework(const Maze::Element& config, std::string client_ip, boost::beast::http::request<boost::beast::http::string_body>* request, boost::beast::http::response<boost::beast::http::string_body>* response) {
        if (_framework_activator) {
            _framework_instance = _framework_activator(config, client_ip, request, response);
        
            return _framework_instance;
        }

        if (_parent)
            return _parent->activate_framework(config, client_ip, request, response);

        throw Exceptions::VortexException("Unable to activate framework", "Dependency injection resolve failed. No applicable activator installed.");
    }

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
