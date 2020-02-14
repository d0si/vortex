#ifndef VORTEX_CORE_FRAMEWORK_FRAMEWORK_H
#define VORTEX_CORE_FRAMEWORK_FRAMEWORK_H

#include <string>
#include <boost/beast/http.hpp>
#include <maze/object.h>
#include <core/framework/router.h>
#include <core/framework/host.h>
#include <core/framework/application.h>
#include <core/framework/controller.h>
#include <core/framework/view.h>
#include <core/storage/mongo/mongo.h>
#include <core/redis/redis.h>
#include <core/script/script.h>

namespace vortex {
namespace core {
namespace framework {

class framework {
 public:
  std::string client_ip_;
  boost::beast::http::request<boost::beast::http::string_body>* request_;
  boost::beast::http::response<boost::beast::http::string_body>* response_;
  maze::object config_;
  redis::redis* redis_;

  router router_;
  host host_;
  application application_;
  controller controller_;
  view view_;
  storage::mongo::mongo mongo_;
  script::script script_;

  framework(
    maze::object config,
    redis::redis* redis,
    std::string client_ip,
    boost::beast::http::request<boost::beast::http::string_body>* request,
    boost::beast::http::response<boost::beast::http::string_body>* response);

  void setup();
  void run();
  void exit();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_FRAMEWORK_H
