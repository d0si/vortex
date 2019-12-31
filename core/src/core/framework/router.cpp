#include <core/framework/router.h>
#include <core/framework/framework.h>

namespace vortex {
namespace core {
namespace framework {

router::router(framework* framework) : framework_(framework) {
  lang_ = "en";
  controller_ = "index";

  std::string target = framework_->request_->target().to_string();
  request_uri_ = target.substr(1, target.length() - 1);
}

void router::setup() {
  // TODO(Ziga)
}

std::string router::get_hostname() {
  return framework_->request_->base()[boost::beast::http::field::host].to_string();
}

std::string router::get_lang() {
  return lang_;
}

std::string router::get_controller() {
  return controller_;
}

std::vector<std::string> router::get_args() {
  return args_;
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
