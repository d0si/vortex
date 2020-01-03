#ifndef VORTEX_CORE_SCRIPT_DUKTAPE_H
#define VORTEX_CORE_SCRIPT_DUKTAPE_H

namespace duk {
class Context;
}

namespace vortex {
namespace core {
namespace script {

class duktape {
 private:
  duk::Context* ctx_;

 public:
  duktape();
  ~duktape();
};

}  // namespace script
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_SCRIPT_DUKTAPE_H
