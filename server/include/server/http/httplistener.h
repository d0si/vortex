#ifndef VORTEX_SERVER_HTTP_HTTP_LISTENER_H
#define VORTEX_SERVER_HTTP_HTTP_LISTENER_H

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <maze/object.h>
#include <Core/Cache/Redis.h>

namespace Vortex {
	namespace Server {
		namespace Http {
			class HttpListener : public std::enable_shared_from_this<HttpListener> {
			private:
				boost::asio::io_context& ioC_;
				boost::asio::ip::tcp::acceptor acceptor_;
				maze::object config_;
				Vortex::Core::Cache::Redis* redis_;

			public:
				HttpListener(
					maze::object config,
					Vortex::Core::Cache::Redis* redis,
					boost::asio::io_context& ioC,
					boost::asio::ip::tcp::endpoint endpoint);

				void run();
				void do_accept();
				void on_accept(
					boost::system::error_code ec,
					boost::asio::ip::tcp::socket socket);
			};
		}  // namespace Http
	}  // namespace Server
}  // namespace Vortex

#endif  // VORTEX_SERVER_HTTP_HTTP_LISTENER_H
