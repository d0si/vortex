#ifndef VORTEX_CORE_SCRIPT_DUKTAPE_H
#define VORTEX_CORE_SCRIPT_DUKTAPE_H

#include <string>

namespace duk {
class Context;
}

namespace vortex {
namespace core {
namespace framework {
class Framework;
}  // namespace framework

namespace script {

class Duktape {
 private:
  duk::Context* ctx_;
  framework::Framework* framework_;

 public:
  Duktape(framework::Framework* framework);
  ~Duktape();

  void setup();
  void exec(std::string script);
};

}  // namespace script
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_SCRIPT_DUKTAPE_H
