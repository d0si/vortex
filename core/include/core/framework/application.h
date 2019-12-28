#ifndef VORTEX_CORE_FRAMEWORK_APPLICATION_H
#define VORTEX_CORE_FRAMEWORK_APPLICATION_H

#include <string>

namespace vortex {
namespace core {
namespace framework {

class Framework;

class Application {
 private:
  Framework* framework_;

 public:
  Application(Framework* framework);

  void find(std::string appId);

  std::string getId();
  std::string getTitle();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_APPLICATION_H
