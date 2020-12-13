#pragma once

#include <Core/Interfaces.h>

namespace Vortex::VortexFramework {

    class Controller : public Core::ControllerInterface {
    public:
        VORTEX_CORE_API Controller(Core::FrameworkInterface* framework);
        VORTEX_CORE_API virtual ~Controller() override = default;

        VORTEX_CORE_API virtual void init(const std::string& application_id,
            const std::string& name, const std::string& method) override;

        VORTEX_CORE_API virtual std::string id() override;
        VORTEX_CORE_API virtual std::string name() override;
        VORTEX_CORE_API virtual Maze::Element app_ids() override;
        VORTEX_CORE_API virtual std::string script() override;
        VORTEX_CORE_API virtual std::string post_script() override;
        VORTEX_CORE_API virtual std::string content_type() override;
        VORTEX_CORE_API virtual std::string method() override;

    protected:
        Maze::Element _controller;
    };

}  // namespace Vortex::VortexFramework
