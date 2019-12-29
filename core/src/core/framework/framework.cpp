#include "core/framework/framework.h"

namespace vortex {
namespace core {
namespace framework {

Framework::Framework(
  maze::MazeObject server_params,
  std::string client_ip,
  boost::beast::http::request<boost::beast::http::string_body>* request,
  boost::beast::http::response<boost::beast::http::string_body>* response
)
    : server_params_(server_params),
    client_ip_(client_ip),
    request_(request),
    response_(response),
    router_(this),
    host_(this),
    application_(this),
    controller_(this),
    view_(this) {
}

void Framework::setup() {
  host_.find(router_.getHost());

  // TODO(Ziga)
}

void Framework::run() {
  // TODO(Ziga)

  throw(0);
}

void Framework::exit() {
  view_.respond();

  throw(0);
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
