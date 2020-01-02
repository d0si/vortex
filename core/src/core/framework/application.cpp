#include <core/framework/application.h>
#include <core/framework/framework.h>

namespace vortex {
namespace core {
namespace framework {

application::application(framework* framework) : framework_(framework) {
}

void application::find(std::string app_id) {
  std::string redis_key = "vortex.core.application.value." + app_id;
  if (framework_->redis_->exists(redis_key)) {
    application_ = maze::object::from_json(framework_->redis_->get(redis_key));
  }

  if (application_.is_empty()) {
    application_ = framework_->mongo_
            .get_collection("apps")
            .find_by_id(app_id);

    if (!application_.is_empty()) {
      framework_->redis_->set(redis_key, application_.to_json(0));
    }
  }

  if (application_.is_empty()) {
    framework_->view_.echo("Application associated with this hostname does not exist");
    framework_->exit();
  }
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
