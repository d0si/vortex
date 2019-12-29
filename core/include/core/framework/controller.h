#ifndef VORTEX_CORE_FRAMEWORK_CONTROLLER_H
#define VORTEX_CORE_FRAMEWORK_CONTROLLER_H

#include <string>

namespace vortex {
namespace core {
namespace framework {

class framework;

class controller {
 private:
  framework* framework_;

 public:
  controller(framework* framework);

  void find(std::string app_id, std::string name, std::string method);
  void run();

  std::string get_id();
  std::string get_name();
  std::string get_script();
  std::string get_content_type();
  std::string get_method();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_CONTROLLER_H
