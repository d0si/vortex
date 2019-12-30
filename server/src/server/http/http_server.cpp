#include <server/http/http_server.h>
#include <iostream>
#include <thread>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <server/http/http_listener.h>

using std::string;
using std::vector;
namespace ip = boost::asio::ip;

namespace vortex {
namespace server {
namespace http {

void http_server::start(maze::object config) {
  config_ = config;

  unsigned short port = (unsigned short)config_.get("port").get_int();

  ip::address address;

  address = ip::make_address("0.0.0.0");

  int threadCount = 4;

  try {
    boost::asio::io_context ioContext{ threadCount };

    std::make_shared<http_listener>(
      config_,
      ioContext,
      ip::tcp::endpoint{ address, port })
      ->run();

    std::cout << "Starting http server on port " << port << std::endl;

    vector<std::thread> threads;
    threads.reserve(threadCount - 1);

    for (int i = threadCount - 1; i > 0; --i) {
      threads.emplace_back([&ioContext] {
        ioContext.run();
      });
    }

    ioContext.run();
  } catch (std::exception const& e) {
    std::cout << "Server failed to start. " << e.what() << std::endl;
  }
}

}  // namespace http
}  // namespace server
}  // namespace vortex
