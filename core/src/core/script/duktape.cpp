#include <core/script/duktape.h>
#include <duktape-cpp/DuktapeCpp.h>

namespace vortex {
namespace core {
namespace script {

duktape::duktape() {
  ctx_ = new duk::Context();
}

duktape::~duktape() {
  delete ctx_;
}

}  // namespace script
}  // namespace core
}  // namespace vortex
