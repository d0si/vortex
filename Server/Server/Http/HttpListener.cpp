#include <Server/Http/HttpListener.h>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <Core/Logging.h>
#include <Server/Http/HttpSession.h>

namespace asio = boost::asio;
namespace beast = boost::beast;
using asio::ip::tcp;
using boost::system::error_code;

namespace Vortex::Server::Http {

    HttpListener::HttpListener(
        const Maze::Element& config,
        asio::io_context& io_ctx,
        tcp::endpoint endpoint,
        Core::Modules::DependencyInjector* server_di)
        : _config(config), _io_ctx(io_ctx), _acceptor(asio::make_strand(io_ctx)), _server_di(server_di) {
        error_code ec;

        _acceptor.open(endpoint.protocol(), ec);
        if (ec) {
            VORTEX_CRITICAL("Listener open failed. {0}", ec.message());

            return;
        }

        _acceptor.set_option(asio::socket_base::reuse_address(true), ec);
        if (ec) {
            VORTEX_CRITICAL("Listener set option REUSE_ADDRESS failed. {0}", ec.message());

            return;
        }

        _acceptor.bind(endpoint, ec);
        if (ec) {
            VORTEX_CRITICAL("Listener bind failed. {0}", ec.message());

            return;
        }

        _acceptor.listen(asio::socket_base::max_listen_connections, ec);
        if (ec) {
            VORTEX_CRITICAL("Listener listen failed. {0}", ec.message());

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
            VORTEX_CRITICAL("Listener accept failed. {0}", ec.message());
        }
        else {
            std::make_shared<HttpSession>(
                _config,
                std::move(socket),
                _server_di->di_scope())
                ->run();
        }

        do_accept();
    }

}
