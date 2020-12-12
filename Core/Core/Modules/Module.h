#pragma once

#include <Core/DLLSupport.h>
#include <string>
#include <vector>

namespace Vortex::Core::Modules {

    class Plugin;

    class Module {
    public:
        VORTEX_CORE_API virtual ~Module() = default;

        VORTEX_CORE_API virtual const std::string module_name() const = 0;

        VORTEX_CORE_API virtual const std::vector<std::string> plugin_names() = 0;
        VORTEX_CORE_API virtual Plugin* plugin(const std::string& plugin_name) = 0;
    };

}  // namespace Vortex::Core::Modules

extern "C" VORTEX_CORE_API_E Vortex::Core::Modules::Module * get_vortex_module(void);

extern "C" VORTEX_CORE_API_E inline const char* get_vortex_module_name(void);
