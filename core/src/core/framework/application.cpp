#include <core/framework/application.h>
#include <core/framework/framework.h>

namespace vortex {
namespace core {
namespace framework {

application::application(framework* framework) : framework_(framework) {
}

void application::find(std::string appId) {
}

std::string application::get_id() {
  return "";
}

std::string application::get_title() {
    return "";
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
