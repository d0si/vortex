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

namespace Vortex::Server::Http {

    HttpListener::HttpListener(
        const Maze::Element& config,
        asio::io_context& io_ctx,
        tcp::endpoint endpoint)
        : _config(config), _io_ctx(io_ctx), _acceptor(asio::make_strand(io_ctx)) {
        error_code ec;

        _acceptor.open(endpoint.protocol(), ec);
        if (ec) {
            std::cout << "Listener open failed. " << ec.message() << std::endl;

            return;
        }

        _acceptor.set_option(asio::socket_base::reuse_address(true), ec);
        if (ec) {
            std::cout << "Listener set option REUSE_ADDRESS failed. "
                << ec.message() << std::endl;

            return;
        }

        _acceptor.bind(endpoint, ec);
        if (ec) {
            std::cout << "Listener bind failed. " << ec.message() << std::endl;

            return;
        }

        _acceptor.listen(asio::socket_base::max_listen_connections, ec);
        if (ec) {
            std::cout << "Listener listen failed. " << ec.message() << std::endl;

            return;
        }
    }

    void HttpListener::run() {
        if (!_acceptor.is_open()) {
            return;
        }

        do_accept();
    }

    void HttpListener::do_accept() {
        _acceptor.async_accept(
            asio::make_strand(_io_ctx),
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
                _config,
                std::move(socket))
                ->run();
        }

        do_accept();
    }

}
