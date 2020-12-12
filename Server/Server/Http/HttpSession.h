#pragma once

#include <boost/asio/strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <Maze/Maze.hpp>

namespace Vortex::Server::Http {

	class HttpSession : public std::enable_shared_from_this<HttpSession> {
	public:
		explicit HttpSession(
			const Maze::Element& config,
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

	private:
		boost::beast::tcp_stream _stream;
		boost::beast::flat_buffer _buffer;
		boost::beast::http::request<boost::beast::http::string_body> _req;
		boost::beast::http::response<boost::beast::http::string_body> _res;
		Maze::Element _config;
	};

}  // namespace Vortex::Server::Http
