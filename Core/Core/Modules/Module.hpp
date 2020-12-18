#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Core/DLLSupport.hpp>
#include <Core/Modules/Plugin.hpp>

namespace Vortex::Core::Modules {

    class DependencyInjector;

    class Module {
    public:
        VORTEX_CORE_API virtual ~Module() = default;

        VORTEX_CORE_API virtual const std::string module_name() const = 0;

        VORTEX_CORE_API virtual const std::vector<std::string> plugin_names() = 0;
        VORTEX_CORE_API virtual Plugin* plugin(const std::string& plugin_name) = 0;

        VORTEX_CORE_API virtual void register_di(const std::shared_ptr<DependencyInjector>& di) = 0;
    };

}  // namespace Vortex::Core::Modules

extern "C" VORTEX_CORE_API_E Vortex::Core::Modules::Module * get_vortex_module(void);

extern "C" VORTEX_CORE_API_E const char* get_vortex_module_name(void);
