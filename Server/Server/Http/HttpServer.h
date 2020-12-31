#pragma once

#include <Maze/Maze.hpp>
#include <Server/DLLSupport.h>
#include <Core/Modules/DependencyInjection.h>

namespace Vortex::Server::Http {

    class HttpServer {
    public:
        VORTEX_SERVER_API void start(const Maze::Element& config, Core::Modules::DependencyInjector* di);

    private:
        Maze::Element _config;
        Core::Modules::DependencyInjector* _server_di;
    };

}  // namespace Vortex::Server::Http
