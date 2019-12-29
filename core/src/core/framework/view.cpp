#include <core/framework/view.h>
#include <core/framework/framework.h>

namespace vortex {
namespace core {
namespace framework {

view::view(framework* framework) : framework_(framework) {
}

void view::output() {
  // TODO(Ziga): Render from template

  respond();
}

void view::respond() {
  framework_->response_->body() = rendered_;
}

void view::echo(std::string contents) {
  rendered_ += contents;
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
