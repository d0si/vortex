#ifndef VORTEX_CORE_FRAMEWORK_APPLICATION_H
#define VORTEX_CORE_FRAMEWORK_APPLICATION_H

#include <string>
#include <maze/object.h>

namespace vortex {
namespace core {
namespace framework {

class Framework;

class Application {
 private:
  Framework* framework_;
  maze::object application_;

 public:
  Application(Framework* framework);

  void find(std::string app_id);

  std::string get_id();
  std::string get_title();
  maze::object get_config();
  std::string get_script();
  std::string get_post_script();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_APPLICATION_H
