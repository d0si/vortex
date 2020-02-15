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

class Framework {
 public:
  std::string client_ip_;
  boost::beast::http::request<boost::beast::http::string_body>* request_;
  boost::beast::http::response<boost::beast::http::string_body>* response_;
  maze::object config_;
  redis::Redis* redis_;

  Router router_;
  Host host_;
  Application application_;
  Controller controller_;
  View view_;
  storage::mongo::Mongo mongo_;
  script::Script script_;

  Framework(
    maze::object config,
    redis::Redis* redis,
    std::string client_ip,
    boost::beast::http::request<boost::beast::http::string_body>* request,
    boost::beast::http::response<boost::beast::http::string_body>* response);

  void setup();
  void run();
  void exit();

  maze::object get_config();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_FRAMEWORK_H
