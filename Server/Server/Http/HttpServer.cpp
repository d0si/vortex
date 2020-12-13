#include <Server/Http/HttpServer.h>
#include <iostream>
#include <thread>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <Server/Http/HttpListener.h>
#include <Core/CommonRuntime.h>

using std::string;
using std::vector;
namespace ip = boost::asio::ip;

namespace Vortex::Server::Http {

    void HttpServer::start(const Maze::Element& config, Core::Modules::DependencyInjector* di) {
        _config = config;
        _server_di = di;

        try {
            if (!Core::CommonRuntime::instance().storage()->is_initialized()) {
                Core::CommonRuntime::instance().storage()->initialize(config.get("storage", Maze::Type::Object));
            }

            if (!Core::CommonRuntime::instance().cache()->is_initialized()) {
                Core::CommonRuntime::instance().cache()->initialize(config.get("cache", Maze::Type::Object));
            }
        }
        catch (const std::exception& e) {
            std::cout << "Unable to initialize storage or caching. " << e.what() << std::endl;

            return;
        }

        Maze::Element server_config(Maze::Type::Object);
        if (_config.is_object("server")) {
            server_config = _config.get("server");
        }

        ip::address address;

        if (server_config.is_string("address")) {
            try {
                address = ip::make_address(server_config["address"].get_string());
            }
            catch (...) {
                std::cout << "Server startup error: IP address resolution failed." << std::endl;

                return;
            }
        }
        else {
            address = ip::make_address("127.0.0.1");
        }

        unsigned short port;
        if (server_config.is_int("port")) {
            port = (unsigned short)server_config["port"].get_int();
        }
        else {
            port = 8080;
        }

        int thread_count;
        if (server_config.is_int("thread_count")) {
            thread_count = server_config["thread_count"].get_int();
        }
        else {
            thread_count = 4;
        }

        try {
            boost::asio::io_context io_context{ thread_count };

            std::make_shared<HttpListener>(
                _config,
                io_context,
                ip::tcp::endpoint{ address, port },
                _server_di)
                ->run();

            std::cout << "Starting http server on port " << port << std::endl;

            int thread_count_z = thread_count - 1;
            if (thread_count_z < 1)
                thread_count_z = 1;

            vector<std::thread> threads;
            threads.reserve(thread_count_z);

            for (int i = thread_count_z; i > 0; --i) {
                threads.emplace_back([&io_context] {
                    io_context.run();
                    });
            }

            io_context.run();
        }
        catch (std::exception const& e) {
            std::cout << "Server failed to start. " << e.what() << std::endl;
        }
    }

}
