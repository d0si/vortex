#include "core/framework/controller.h"
#include "core/framework/framework.h"

namespace vortex {
namespace core {
namespace framework {

Controller::Controller(Framework* framework) : framework_(framework) {
}

void Controller::find(std::string appId, std::string name, std::string method) {
}

void Controller::run() {
}

std::string Controller::getId() {
  return "";
}

std::string Controller::getName() {
  return "";
}

std::string Controller::getScript() {
  return "";
}

std::string Controller::getContentType() {
  return "";
}

std::string Controller::getMethod() {
  return "";
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
