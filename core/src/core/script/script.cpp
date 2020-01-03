#include <core/script/script.h>
#include <core/framework/framework.h>

namespace vortex {
namespace core {
namespace script {

script::script(framework::framework *framework)
  : framework_(framework), duktape_(framework) {

}

void script::setup() {
  duktape_.setup();
}

void script::exec(std::string script) {
  duktape_.exec(script);
}

}  // namespace script
}  // namespace core
}  // namespace vortex
