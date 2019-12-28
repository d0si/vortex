#include "core/framework/view.h"
#include "core/framework/framework.h"

namespace vortex {
namespace core {
namespace framework {

View::View(Framework* framework) : framework_(framework) {
}

void View::output() {
  // TODO(Ziga): Render from template

  respond();
}

void View::respond() {
  framework_->response_->body() = rendered_;
}

void View::echo(std::string contents) {
  rendered_ += contents;
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
