#pragma once

#include <Core/Modules/Module.h>

namespace Vortex::VortexFramework {

    class VortexModule : public Core::Modules::Module {
    public:
        static const std::string s_module_name;

        virtual const std::string module_name() const override;

        virtual const std::vector<std::string> plugin_names() override;
        virtual Core::Modules::Plugin* plugin(const std::string& plugin_name) override;

        virtual void register_di(Core::Modules::DependencyInjector* di) override;
    };

}  // namespace Vortex::VortexFramework
