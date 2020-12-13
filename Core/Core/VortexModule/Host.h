#pragma once

#include <Core/Interfaces.h>

namespace Vortex::Core::VortexModule {

    class Host : public HostInterface {
    public:
        VORTEX_CORE_API Host(FrameworkInterface* framework);
        VORTEX_CORE_API virtual ~Host() override = default;

        VORTEX_CORE_API virtual void init(const std::string& hostname) override;

        VORTEX_CORE_API virtual std::string id() override;
        VORTEX_CORE_API virtual std::string hostname() override;
        VORTEX_CORE_API virtual std::string application_id() override;
        VORTEX_CORE_API virtual Maze::Element config() override;
        VORTEX_CORE_API virtual std::string script() override;
        VORTEX_CORE_API virtual std::string post_script() override;

    protected:
        Maze::Element _host;
    };

}  // namespace Vortex::Core::VortexModule
