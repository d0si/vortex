#ifndef VORTEX_CORE_FRAMEWORK_APPLICATION_H
#define VORTEX_CORE_FRAMEWORK_APPLICATION_H

#include <string>
#include <maze/object.h>

namespace vortex {
namespace core {
namespace framework {

class framework;

class application {
 private:
  framework* framework_;
  maze::object application_;

 public:
  application(framework* framework);

  void find(std::string app_id);

  std::string get_id();
  std::string get_title();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_APPLICATION_H
