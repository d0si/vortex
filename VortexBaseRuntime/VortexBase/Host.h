#pragma once

#include <Core/Interfaces.h>

namespace VortexBase {

    class Host : public Vortex::Core::HostInterface {
    public:
        VORTEX_CORE_API Host(Vortex::Core::RuntimeInterface* runtime);
        VORTEX_CORE_API virtual ~Host() override = default;

        VORTEX_CORE_API virtual void init(const std::string& hostname) override;

        VORTEX_CORE_API virtual std::string id() override;
        VORTEX_CORE_API virtual std::string hostname() override;
        VORTEX_CORE_API virtual std::string application_id() override;
        VORTEX_CORE_API virtual Maze::Element config() override;
        VORTEX_CORE_API virtual std::string script() override;
        VORTEX_CORE_API virtual std::string post_script() override;
    };

}  // namespace VortexBase
