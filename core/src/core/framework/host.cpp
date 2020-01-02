#include <core/framework/router.h>
#include <core/framework/framework.h>
#include <maze/element.h>

namespace vortex {
namespace core {
namespace framework {

host::host(framework* framework) : framework_(framework) {
}

void host::find(std::string hostname) {
  std::string redis_key = "vortex.core.host.value." + hostname;
  if (framework_->redis_->exists(redis_key)) {
    host_ = maze::object::from_json(framework_->redis_->get(redis_key));
  }

  if (host_.is_empty()) {
    host_ = framework_->mongo_
            .get_collection("hosts")
            .find_one(maze::object("hostname", hostname));

    if (!host_.is_empty()) {
      framework_->redis_->set(redis_key, host_.to_json(0));
    }
  }

  if (host_.is_empty()) {
    framework_->view_.echo("Nothing is running on this hostname");
    framework_->exit();
  }
}

std::string host::get_id() {
    return host_["_id"].get_object()["$oid"].get_string();
}

std::string host::get_hostname() {
    return host_["hostname"].get_string();
}

std::string host::get_app_id() {
    return host_["app_id"].get_string();
}

maze::object host::get_config() {
  return host_["config"].get_object();
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
