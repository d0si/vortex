#ifndef VORTEX_SERVER_HTTP_SESSION_H
#define VORTEX_SERVER_HTTP_SESSION_H

#include <boost/asio/strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <maze/maze_object.h>

namespace vortex {
namespace server {
namespace http {

class HttpSession : public std::enable_shared_from_this<HttpSession> {
 private:
  boost::beast::tcp_stream stream_;
  boost::beast::flat_buffer buffer_;
  boost::beast::http::request<boost::beast::http::string_body> req_;
  boost::beast::http::response<boost::beast::http::string_body> res_;
  maze::maze_object server_params_;

 public:
  explicit HttpSession(maze::maze_object server_params, boost::asio::ip::tcp::socket socket);

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

}  // namespace http
}  // namespace server
}  // namespace vortex

#endif  // VORTEX_SERVER_HTTP_SESSION_H
