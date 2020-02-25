#include <Server/Http/HttpListener.h>
#include <iostream>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <Server/Http/HttpSession.h>

namespace asio = boost::asio;
namespace beast = boost::beast;
using asio::ip::tcp;
using boost::system::error_code;

namespace Vortex {
	namespace Server {
		namespace Http {
			HttpListener::HttpListener(
				maze::object config,
				Vortex::Core::Cache::Redis* redis,
				asio::io_context& ioC,
				tcp::endpoint endpoint)
				: config_(config), redis_(redis), ioC_(ioC), acceptor_(asio::make_strand(ioC)) {
				error_code ec;

				acceptor_.open(endpoint.protocol(), ec);
				if (ec) {
					std::cout << "Listener open failed. " << ec.message() << std::endl;

					return;
				}

				acceptor_.set_option(asio::socket_base::reuse_address(true), ec);
				if (ec) {
					std::cout << "Listener set option REUSE_ADDRESS failed. "
						<< ec.message() << std::endl;

					return;
				}

				acceptor_.bind(endpoint, ec);
				if (ec) {
					std::cout << "Listener bind failed. " << ec.message() << std::endl;

					return;
				}

				acceptor_.listen(asio::socket_base::max_listen_connections, ec);
				if (ec) {
					std::cout << "Listener listen failed. " << ec.message() << std::endl;

					return;
				}
			}

			void HttpListener::run() {
				if (!acceptor_.is_open()) {
					return;
				}

				do_accept();
			}

			void HttpListener::do_accept() {
				acceptor_.async_accept(
					asio::make_strand(ioC_),
					beast::bind_front_handler(
						&HttpListener::on_accept,
						shared_from_this()));
			}

			void HttpListener::on_accept(error_code ec, tcp::socket socket) {
				if (ec) {
					std::cout << "Listener accept failed. " << ec.message() << std::endl;
				}
				else {
					std::make_shared<HttpSession>(
						config_,
						redis_,
						std::move(socket))
						->run();
				}

				do_accept();
			}
		}  // namespace Http
	}  // namespace Server
}  // namespace Vortex
