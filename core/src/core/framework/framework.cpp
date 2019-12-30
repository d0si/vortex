#include <core/framework/framework.h>

namespace vortex {
namespace core {
namespace framework {

framework::framework(
  maze::object config,
  std::string client_ip,
  boost::beast::http::request<boost::beast::http::string_body>* request,
  boost::beast::http::response<boost::beast::http::string_body>* response
)
    : config_(config),
    client_ip_(client_ip),
    request_(request),
    response_(response),
    router_(this),
    host_(this),
    application_(this),
    controller_(this),
    view_(this) {
}

void framework::setup() {
  host_.find(router_.get_host());

  // TODO(Ziga)
}

void framework::run() {
  // TODO(Ziga)

  throw(0);
}

void framework::exit() {
  view_.respond();

  throw(0);
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
