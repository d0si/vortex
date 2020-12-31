#pragma once

#include <Core/Modules/Plugin.h>

namespace Vortex::App::Db::Plugins {

    class DbControllerPlugin : public Vortex::Core::Modules::Plugin {
    public:
        static const std::string s_plugin_name;

        virtual const std::string plugin_name() const override;
        virtual Vortex::Core::Modules::PluginExecutePoint execute_point() override;

        virtual bool execute_before(Vortex::Core::RuntimeInterface* runtime, void* data) override;  
    };

}  // namespace Vortex::App::Db::Plugins
