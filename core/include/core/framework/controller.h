#ifndef VORTEX_CORE_FRAMEWORK_CONTROLLER_H
#define VORTEX_CORE_FRAMEWORK_CONTROLLER_H

#include <string>

namespace vortex {
namespace core {
namespace framework {

class Framework;

class Controller {
 private:
  Framework* framework_;

 public:
  Controller(Framework* framework);

  void find(std::string appId, std::string name, std::string method);
  void run();

  std::string getId();
  std::string getName();
  std::string getScript();
  std::string getContentType();
  std::string getMethod();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_CONTROLLER_H
