#pragma once

#include <Core/Interfaces.h>

namespace VortexBase {

    class Application : public Vortex::Core::ApplicationInterface {
    public:
        VORTEX_CORE_API Application(Vortex::Core::RuntimeInterface* runtime);
        VORTEX_CORE_API virtual ~Application() override = default;

        VORTEX_CORE_API virtual void init(const std::string& app_id) override;

        VORTEX_CORE_API virtual std::string id() override;
        VORTEX_CORE_API virtual std::string title() override;
        VORTEX_CORE_API virtual Maze::Element config() override;
        VORTEX_CORE_API virtual std::string script() override;
        VORTEX_CORE_API virtual std::string post_script() override;

        VORTEX_CORE_API virtual Maze::Element find_object_in_application_storage(
            const std::string& collection, const Maze::Element& query,
            bool search_other_storages = true) override;
    };

}  // namespace VortexBase
