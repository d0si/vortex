#include <core/framework/application.h>
#include <core/framework/framework.h>

namespace vortex {
namespace core {
namespace framework {

application::application(framework* framework) : framework_(framework) {
}

void application::find(std::string app_id) {
  application_ = framework_->mongo_
    .get_collection("apps")
    .find_by_id(app_id);
}

std::string application::get_id() {
  return application_["_id"].get_object()["$oid"].get_string();
}

std::string application::get_title() {
  return application_["title"].get_string();
}

maze::object application::get_config() {
  return application_["config"].get_object();
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
