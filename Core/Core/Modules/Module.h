#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Core/DLLSupport.h>
#include <Core/Modules/Plugin.h>

namespace Vortex::Core::Modules {

    class DependencyInjector;

    class Module {
    public:
        VORTEX_CORE_API virtual ~Module() = default;

        VORTEX_CORE_API virtual const std::string module_name() const = 0;

        VORTEX_CORE_API virtual const std::vector<std::string> plugin_names() = 0;
        VORTEX_CORE_API virtual std::shared_ptr<Plugin> plugin(const std::string& plugin_name) = 0;

        VORTEX_CORE_API virtual void register_di(DependencyInjector* di) = 0;
    };

}  // namespace Vortex::Core::Modules

extern "C" VORTEX_CORE_API_E Vortex::Core::Modules::Module * get_vortex_module(void);

extern "C" VORTEX_CORE_API_E const char* get_vortex_module_name(void);
