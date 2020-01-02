#include <core/framework/framework.h>
#include <maze/element.h>

namespace vortex {
namespace core {
namespace framework {

framework::framework(
  maze::object config,
  redis::redis* redis,
  std::string client_ip,
  boost::beast::http::request<boost::beast::http::string_body>* request,
  boost::beast::http::response<boost::beast::http::string_body>* response
)
    : config_(config),
    redis_(redis),
    client_ip_(client_ip),
    request_(request),
    response_(response),
    router_(this),
    host_(this),
    application_(this),
    controller_(this),
    view_(this) {
  mongo_ = mongo::mongo(config_["mongo"].get_object());
}

void framework::setup() {
  host_.find(router_.get_hostname());
  application_.find(host_.get_app_id());

  config_.apply(application_.get_config());
  config_.apply(host_.get_config());

  router_.setup();

  controller_.find(
    application_.get_id(),
    router_.get_controller(),
    request_->method_string().to_string());
}

void framework::run() {

  controller_.run();

  view_.echo(router_.get_controller());

  view_.output();
  throw(0);
}

void framework::exit() {
  view_.respond();

  throw(0);
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
