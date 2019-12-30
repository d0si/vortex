#include <core/framework/controller.h>
#include <core/framework/framework.h>

namespace vortex {
namespace core {
namespace framework {

controller::controller(framework* framework) : framework_(framework) {
}

void controller::find(std::string app_id, std::string name, std::string method) {
  maze::object query;
  query["app_id"] = app_id;
  query["name"] = name;
  query["method"] = method;

  controller_ = framework_->mongo_
    .get_collection("controllers")
    .find_one(query));
}

void controller::run() {
}

std::string controller::get_id() {
  return controller_["_id"].get_object()["$oid"].get_string();
}

std::string controller::get_name() {
  return controller_["name"].get_string();
}

maze::array controller::get_apps() {
  return controller_["apps"].get_array();
}

std::string controller::get_script() {
  return controller_["script"].get_string();
}

std::string controller::get_content_type() {
  return controller_["content_type"].get_string();
}

std::string controller::get_method() {
  return controller_["method"].get_string();
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
