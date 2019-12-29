#ifndef VORTEX_SERVER_HTTP_LISTENER_H
#define VORTEX_SERVER_HTTP_LISTENER_H

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <maze/mazeObject.h>

namespace vortex {
namespace server {
namespace http {

class HttpListener : public std::enable_shared_from_this<HttpListener> {
 private:
  boost::asio::io_context& ioC_;
  boost::asio::ip::tcp::acceptor acceptor_;
  maze::MazeObject server_params_;

 public:
  HttpListener(
    maze::MazeObject server_params,
    boost::asio::io_context& ioC,
    boost::asio::ip::tcp::endpoint endpoint);

  void run();
  void do_accept();
  void on_accept(
    boost::system::error_code ec,
    boost::asio::ip::tcp::socket socket);
};

}  // namespace http
}  // namespace server
}  // namespace vortex

#endif  // VORTEX_SERVER_HTTP_LISTENER_H
