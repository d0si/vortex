#include "core/framework/router.h"
#include "core/framework/framework.h"

namespace vortex {
namespace core {
namespace framework {

Router::Router(Framework* framework) : framework_(framework) {
  lang_ = "en";
  controller_ = "index";

  std::string target = framework_->request_->target().to_string();
  request_uri_ = target.substr(1, target.length() - 1);
}

void Router::setup() {
  // TODO(Ziga)
}

std::string Router::getHost() {
  return framework_->request_->base()[boost::beast::http::field::host].to_string();
}

std::string Router::getLang() {
  return lang_;
}

std::string Router::getController() {
  return controller_;
}

std::vector<std::string> Router::getArgs() {
  return args_;
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
