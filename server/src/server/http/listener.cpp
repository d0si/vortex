#include "server/http/listener.h"
#include <iostream>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;
using boost::system::error_code;

namespace vortex {
namespace server {
namespace http {

HttpListener::HttpListener(asio::io_context& ioC, tcp::endpoint endpoint)
    : acceptor_(ioC), socket_(ioC) {
  error_code ec;

  acceptor_.open(endpoint.protocol(), ec);
  if (ec) {
    std::cout << "Listener open failed. " << ec.message() << std::endl;

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
  acceptor_.async_accept(socket_, std::bind(
    &HttpListener::on_accept,
    shared_from_this(),
    std::placeholders::_1
  ));
}

void HttpListener::on_accept(error_code ec) {
  if (ec) {
    std::cout << "Listener accept failed. " << ec.message() << std::endl;
  } else {
    // std::make_shared<HttpSession>(
    //   std::move(socket_)
    // )->run();
  }

  do_accept();
}

}  // namespace http
}  // namespace server
}  // namespace vortex
