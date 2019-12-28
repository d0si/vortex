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

HttpSession::HttpSession(tcp::socket socket)
    : stream_(std::move(socket)) {

}

void HttpSession::run() {
  do_read();
}

void HttpSession::do_read() {
  req_ = {};

  stream_.expires_after(std::chrono::seconds(30));

  beast::http::async_read(stream_, buffer_, req_, beast::bind_front_handler(
      &HttpSession::on_read,
      shared_from_this()));
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

  // TODO(ziga)
}

void HttpSession::on_write(
    bool close,
    error_code ec,
    std::size_t bytes_transferred) {
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

  stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
}

void HttpSession::send() {
  beast::http::async_write(stream_, res_, beast::bind_front_handler(
    &HttpSession::on_write,
    shared_from_this(),
    res_.need_eof()));
}

}  // namespace http
}  // namespace server
}  // namespace vortex
