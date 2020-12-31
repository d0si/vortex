#pragma once

#include <Core/Modules/Plugin.h>

namespace ModuleSample::Plugins {

    class SamplePlugin : public Vortex::Core::Modules::Plugin {
    public:
        virtual const std::string plugin_name() const override;
    };

}  // namespace ModuleSample::Plugins
