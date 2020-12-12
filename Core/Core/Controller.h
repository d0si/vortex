#pragma once

#include <string>
#include <Maze/Maze.hpp>
#include <Core/DLLSupport.h>

namespace Vortex::Core {

    class Framework;


    class Controller {
    public:
        VORTEX_CORE_API Controller(Framework* framework);

        VORTEX_CORE_API void find(std::string app_id, std::string name, std::string method);

        VORTEX_CORE_API const std::string& get_id() const;
        VORTEX_CORE_API const std::string& get_name() const;
        VORTEX_CORE_API const Maze::Element get_app_ids() const;
        VORTEX_CORE_API const std::string& get_script() const;
        VORTEX_CORE_API const std::string& get_post_script() const;
        VORTEX_CORE_API const std::string& get_content_type() const;
        VORTEX_CORE_API const std::string& get_method() const;

    private:
        Framework* _framework;
        Maze::Element _controller;
    };

}  // namespace Vortex::Core
