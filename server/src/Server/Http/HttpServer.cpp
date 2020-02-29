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

namespace Vortex {
	namespace Server {
		namespace Http {
			void HttpServer::start(Maze::Object config) {
				this->config_ = config;

				if (!Core::CommonRuntime::Instance.get_storage()->is_initialized()) {
					Core::CommonRuntime::Instance.get_storage()->initialize(config["storage"].get_object());
				}

				redis_.set_config(config_["redis"].get_object());
				redis_.connect();

				Maze::Object server_config;
				if (config_.is_object("server")) {
					server_config = config_["server"].get_object();
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
					boost::asio::io_context ioContext{ thread_count };

					std::make_shared<HttpListener>(
						config_,
						&redis_,
						ioContext,
						ip::tcp::endpoint{ address, port })
						->run();

					std::cout << "Starting http server on port " << port << std::endl;

					vector<std::thread> threads;
					threads.reserve(thread_count - 1);

					for (int i = thread_count - 1; i > 0; --i) {
						threads.emplace_back([&ioContext] {
							ioContext.run();
							});
					}

					ioContext.run();
				}
				catch (std::exception const& e) {
					std::cout << "Server failed to start. " << e.what() << std::endl;
				}
			}
		}  // namespace Http
	}  // namespace Server
}  // namespace Vortex
