#ifndef VORTEX_CORE_FRAMEWORK_APPLICATION_H
#define VORTEX_CORE_FRAMEWORK_APPLICATION_H

#include <string>

namespace vortex {
namespace core {
namespace framework {

class framework;

class application {
 private:
  framework* framework_;

 public:
  application(framework* framework);

  void find(std::string appId);

  std::string get_id();
  std::string get_title();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_APPLICATION_H
