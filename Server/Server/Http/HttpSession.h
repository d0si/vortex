#ifndef VORTEX_SERVER_HTTP_HTTP_SESSION_H
#define VORTEX_SERVER_HTTP_HTTP_SESSION_H

#include <boost/asio/strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <Maze/Object.hpp>

namespace Vortex {
	namespace Server {
		namespace Http {
			class HttpSession : public std::enable_shared_from_this<HttpSession> {
			private:
				boost::beast::tcp_stream stream_;
				boost::beast::flat_buffer buffer_;
				boost::beast::http::request<boost::beast::http::string_body> req_;
				boost::beast::http::response<boost::beast::http::string_body> res_;
				Maze::Object config_;

			public:
				explicit HttpSession(
					Maze::Object config,
					boost::asio::ip::tcp::socket socket);

				void run();
				void do_read();
				void on_read(boost::system::error_code ec, std::size_t bytes_transferred);
				void on_write(
					bool close,
					boost::system::error_code ec,
					std::size_t bytes_transferred);
				void do_close();
				void send();
			};
		}  // namespace Http
	}  // namespace Server
}  // namespace Vortex

#endif  // VORTEX_SERVER_HTTP_HTTP_SESSION_H