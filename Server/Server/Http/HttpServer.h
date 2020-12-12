#pragma once

#include <Maze/Maze.hpp>
#include <Server/DLLSupport.h>

namespace Vortex::Server::Http {

    class HttpServer {
    public:
        VORTEX_SERVER_API void start(const Maze::Element& config);

    private:
        Maze::Element _config;
    };

}  // namespace Vortex::Server::Http
