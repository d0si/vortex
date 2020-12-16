#pragma once

#include <string>
#include <Maze/Maze.hpp>
#include <Core/DLLSupport.h>

namespace Vortex::Core {

    class Framework;


    class Application {
    public:
        VORTEX_CORE_API Application(Framework* framework);

        VORTEX_CORE_API void find(const std::string& app_id);

        VORTEX_CORE_API const std::string& get_id() const;
        VORTEX_CORE_API const std::string& get_title() const;
        VORTEX_CORE_API const Maze::Element get_config() const;
        VORTEX_CORE_API const std::string& get_script() const;
        VORTEX_CORE_API const std::string& get_post_script() const;

        VORTEX_CORE_API Maze::Element find_object_in_application_storage(const std::string& collection, const Maze::Element& query, bool search_other_storages = true) const;

    private:
        Framework* _framework;
        Maze::Element _application;
    };

}  // namespace Vortex::Core
