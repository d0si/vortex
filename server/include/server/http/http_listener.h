#ifndef VORTEX_SERVER_HTTP_HTTP_LISTENER_H
#define VORTEX_SERVER_HTTP_HTTP_LISTENER_H

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <maze/object.h>

namespace vortex {
namespace server {
namespace http {

class http_listener : public std::enable_shared_from_this<http_listener> {
 private:
  boost::asio::io_context& ioC_;
  boost::asio::ip::tcp::acceptor acceptor_;
  maze::object config_;

 public:
  http_listener(
    maze::object config,
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

#endif  // VORTEX_SERVER_HTTP_HTTP_LISTENER_H
