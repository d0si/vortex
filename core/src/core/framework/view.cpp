#include "core/framework/view.h"
#include "core/framework/framework.h"

namespace vortex {
namespace core {
namespace framework {

View::View(Framework* framework) : framework_(framework) {
}

void View::output() {
}

void View::respond() {
}

void View::echo(std::string contents) {
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
