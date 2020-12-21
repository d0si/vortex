#pragma once

#include <string>
#include <Core/DLLSupport.h>

namespace Vortex::Core::Modules {

    class Plugin {
    public:
        virtual ~Plugin() = default;

        virtual const std::string plugin_name() const = 0;
    };

}  // namespace Vortex::Core::Modules
