#include <server/http/httpsession.h>
#include <iostream>
#include <boost/asio/bind_executor.hpp>
#include <boost/beast/http.hpp>
#include <core/framework/framework.h>
#ifdef VORTEX_HAS_FEATURE_MONGO
#include <mongocxx/exception/exception.hpp>
#endif

namespace asio = boost::asio;
namespace beast = boost::beast;
using asio::ip::tcp;
using boost::system::error_code;

namespace vortex {
namespace server {
namespace http {

HttpSession::HttpSession(
  maze::object config,
  vortex::core::redis::Redis* redis,
  tcp::socket socket)
    : config_(config), redis_(redis), stream_(std::move(socket)) {

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

  const clock_t begin_time = clock();
  std::cout << "Request received ("
    << req_.method_string().to_string()
    << ") "
    << req_.target().to_string()
    << std::endl;

  res_.version(req_.version());

  res_.keep_alive(req_.keep_alive());
  if (req_.method() == boost::beast::http::verb::post) {
    res_.keep_alive(false);
  }

  res_.set(boost::beast::http::field::server, "Vortex Framework");
  res_.set(boost::beast::http::field::content_type, "text/html");
  res_.result(boost::beast::http::status::ok);

  core::framework::Framework* framework = nullptr;

  try {
    framework = new core::framework::Framework(
      config_,
      redis_,
      stream_.socket().remote_endpoint().address().to_string(),
      &req_,
      &res_);

    framework->setup();

    framework->run();
  } catch (int e) {

#ifdef VORTEX_HAS_FEATURE_MONGO
  } catch (mongocxx::exception::runtime_error e) {
    res_.result(boost::beast::http::status::internal_server_error);
    std::string what = e.what();
    res_.body() = "MongoDb exception: " + what;
#endif
  } catch (...) {
    res_.result(boost::beast::http::status::internal_server_error);
    res_.body() = "Internal server error";
  }

  if (framework != nullptr) {
    delete framework;
  }

  res_.set(boost::beast::http::field::content_length, res_.body().size());

  std::cout << "Request finished "
    << req_.target().to_string()
    << " ["
    << std::to_string(float(clock() - begin_time) / CLOCKS_PER_SEC)
    << "]"
    << std::endl;

  send();
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
