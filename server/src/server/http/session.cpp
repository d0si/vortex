#include "server/http/session.h"
#include <iostream>
#include <boost/asio/bind_executor.hpp>
#include <boost/beast/http.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
using asio::ip::tcp;
using boost::system::error_code;

namespace vortex {
namespace server {
namespace http {

HttpSession::HttpSession(tcp::socket socket) :
    socket_(std::move(socket)),
    strand_(socket_.get_executor()) {

}

void HttpSession::run() {
  do_read();
}

void HttpSession::do_read() {
  beast::http::async_read(socket_, buffer_, req_,
    asio::bind_executor(
      strand_,
      std::bind(
        &HttpSession.on_read,
        shared_from_this(),
        std::placeholders::_1,
        std::placeholders::_2
      )
    ));
}

void HttpSession::on_read(error_code ec, std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  if (ec == beast::http::error::end_of_stream) {
    return do_close();
  }

  if (ec) {
    std::cout << "HttpSession read failed. " << ec.message() << std::endl;

    return;
  }

  //  TODO
}

void HttpSession::on_write(error_code ec, std::size_t bytes_transferred, bool close) {
  boost::ignore_unused(bytes_transferred);

  if (ec) {
    std::cout << "HttpSession write failed. " << ec.message() << std::endl;

    return;
  }

  if (close) {
    return do_close();
  }

  do_read();
}

void HttpSession::do_close() {
  error_code ec;
  socket_.shutdown(tcp::socket::shutdown_send, ec);
}

void HttpSession::send() {
  beast::http::async_write(socket_, res, asio::bind_executor(
    strand_,
    std::bind(
      &HttpSession::on_write,
      shared_from_this(),
      std::placeholders::_1,
      std::placeholders::_1,
      res.need_eof()
    )
  ));
}

}  // namespace http
}  // namespace server
}  // namespace vortex
