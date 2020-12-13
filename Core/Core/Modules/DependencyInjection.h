#pragma once

#include <Core/DLLSupport.h>
#include <Core/Interfaces.h>
#include <Core/Modules/ModuleLoader.h>

namespace Vortex::Core::Modules {

    class DependencyInjector {
    private:
        class FrameworkInterface* _framework = nullptr;

    public:
        VORTEX_CORE_API DependencyInjector() = default;
        VORTEX_CORE_API DependencyInjector(DependencyInjector* parent);
        VORTEX_CORE_API ~DependencyInjector();

        VORTEX_CORE_API DependencyInjector* di_scope();
        VORTEX_CORE_API DependencyInjector di_scope_temp();
        VORTEX_CORE_API static DependencyInjector* di_global();

        VORTEX_CORE_API void install(FrameworkInterface* (*framework_activate)(const Maze::Element& config, std::string client_ip, boost::beast::http::request<boost::beast::http::string_body>* request, boost::beast::http::response<boost::beast::http::string_body>* response));
        VORTEX_CORE_API FrameworkInterface* activate_framework(const Maze::Element& config, std::string client_ip, boost::beast::http::request<boost::beast::http::string_body>* request, boost::beast::http::response<boost::beast::http::string_body>* response);

        VORTEX_CORE_API static ModuleLoader* module_loader();

        VORTEX_CORE_API void add_ref();
        VORTEX_CORE_API void del_ref();

    private:
        DependencyInjector* _parent = nullptr;
        int _refs_count = 0;

        FrameworkInterface* (*_framework_activator)(const Maze::Element& config, std::string client_ip, boost::beast::http::request<boost::beast::http::string_body>* request, boost::beast::http::response<boost::beast::http::string_body>* response) = nullptr;
        FrameworkInterface* _framework_instance = nullptr;

        static DependencyInjector s_global;
    };

}  // namespace Vortex::Core::Modules
