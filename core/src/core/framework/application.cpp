#include "core/framework/application.h"
#include "core/framework/framework.h"

namespace vortex {
namespace core {
namespace framework {

Application::Application(Framework* framework) : framework_(framework) {
}

void Application::find(std::string appId) {
}

std::string Application::getId() {
  return "";
}

std::string Application::getTitle() {
    return "";
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
