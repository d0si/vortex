#pragma once

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <Maze/Maze.hpp>

namespace Vortex::Server::Http {

	class HttpListener : public std::enable_shared_from_this<HttpListener> {
	public:
		HttpListener(
			const Maze::Element& config,
			boost::asio::io_context& io_ctx,
			boost::asio::ip::tcp::endpoint endpoint);

		void run();
		void do_accept();
		void on_accept(
			boost::system::error_code ec,
			boost::asio::ip::tcp::socket socket);

	private:
		boost::asio::io_context& _io_ctx;
		boost::asio::ip::tcp::acceptor _acceptor;
		Maze::Element _config;
	};

}  // namespace Vortex::Server::Http
