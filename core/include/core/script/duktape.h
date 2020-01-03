#ifndef VORTEX_CORE_SCRIPT_DUKTAPE_H
#define VORTEX_CORE_SCRIPT_DUKTAPE_H

#include <string>

namespace duk {
class Context;
}

namespace vortex {
namespace core {
namespace framework {
class framework;
}  // namespace framework

namespace script {

class duktape {
 private:
  duk::Context* ctx_;
  framework::framework* framework_;

 public:
  duktape(framework::framework* framework);
  ~duktape();

  void setup();
  void exec(std::string script);
};

}  // namespace script
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_SCRIPT_DUKTAPE_H
