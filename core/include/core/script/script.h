#ifndef VORTEX_CORE_SCRIPT_SCRIPT_H
#define VORTEX_CORE_SCRIPT_SCRIPT_H

#include <string>
#include <core/script/duktape.h>

namespace vortex {
namespace core {
namespace framework {
class framework;
}

namespace script {

class script {
private:
  framework::framework* framework_;
  duktape duktape_;

public:
  script(framework::framework* framework);

  void setup();
  void exec(std::string script);
};


}  // namespace script
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_SCRIPT_SCRIPT_H
