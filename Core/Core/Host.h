#pragma once

#include <string>
#include <Maze/Maze.hpp>
#include <Core/DLLSupport.h>

namespace Vortex::Core {

    class Framework;


    class Host {
    public:
        VORTEX_CORE_API Host(Framework* framework);

        VORTEX_CORE_API void find(const std::string& hostname);

        VORTEX_CORE_API const std::string& get_id() const;
        VORTEX_CORE_API const std::string& get_hostname() const;
        VORTEX_CORE_API const std::string& get_app_id() const;
        VORTEX_CORE_API const Maze::Element get_config() const;
        VORTEX_CORE_API const std::string& get_script() const;
        VORTEX_CORE_API const std::string& get_post_script() const;

    private:
        Framework* _framework;
        Maze::Element _host;
    };

}  // namespace Vortex::Core
