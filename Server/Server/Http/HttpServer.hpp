#pragma once

#include <Maze/Maze.hpp>
#include <Server/DLLSupport.hpp>
#include <Core/Modules/DependencyInjection.hpp>

namespace Vortex::Server::Http {

    class HttpServer {
    public:
        VORTEX_SERVER_API void start(const Maze::Element& config, const std::shared_ptr<Core::Modules::DependencyInjector>& di);

    private:
        Maze::Element _config;
        std::shared_ptr<Core::Modules::DependencyInjector> _server_di;
    };

}  // namespace Vortex::Server::Http
