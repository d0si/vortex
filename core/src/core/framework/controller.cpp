#include <core/framework/controller.h>
#include <core/framework/framework.h>

namespace vortex {
namespace core {
namespace framework {

controller::controller(framework* framework) : framework_(framework) {
}

void controller::find(std::string app_id, std::string name, std::string method) {
}

void controller::run() {
}

std::string controller::get_id() {
  return "";
}

std::string controller::get_name() {
  return "";
}

std::string controller::get_script() {
  return "";
}

std::string controller::get_content_type() {
  return "";
}

std::string controller::get_method() {
  return "";
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
