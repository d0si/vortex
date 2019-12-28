#ifndef VORTEX_CORE_FRAMEWORK_FRAMEWORK_H
#define VORTEX_CORE_FRAMEWORK_FRAMEWORK_H

#include <string>
#include <boost/beast/http.hpp>

namespace vortex {
namespace core {
namespace framework {

class Framework {
public:
  std::string client_ip_;
  boost::beast::http::request<boost::beast::http::string_body>* request_;
  boost::beast::http::response<boost::beast::http::string_body>* response_;

  Framework(
    std::string client_ip,
    boost::beast::http::request<boost::beast::http::string_body>* request,
    boost::beast::http::response<boost::beast::http::string_body>* response
  );

  void setup();
  void run();
  void exit();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_FRAMEWORK_H
