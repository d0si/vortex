#include "core/framework/framework.h"

namespace vortex {
namespace core {
namespace framework {

Framework::Framework(
  std::string client_ip,
    boost::beast::http::request<boost::beast::http::string_body>* request,
    boost::beast::http::response<boost::beast::http::string_body>* response
)
    : client_ip_(client_ip), request_(request), response_(response) {
}

void Framework::setup() {
  // TODO(Ziga)
}

void Framework::run() {
  // TODO(Ziga)

  throw(0);
}

void Framework::exit() {
  // TODO(Ziga)

  throw(0);
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
