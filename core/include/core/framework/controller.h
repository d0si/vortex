#ifndef VORTEX_CORE_FRAMEWORK_CONTROLLER_H
#define VORTEX_CORE_FRAMEWORK_CONTROLLER_H

#include <string>
#include <maze/object.h>
#include <maze/array.h>

namespace vortex {
namespace core {
namespace framework {

class Framework;

class Controller {
 private:
  Framework* framework_;
  maze::object controller_;

 public:
  Controller(Framework* framework);

  void find(std::string app_id, std::string name, std::string method);

  std::string get_id();
  std::string get_name();
  maze::array get_app_ids();
  std::string get_script();
  std::string get_post_script();
  std::string get_content_type();
  std::string get_method();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_CONTROLLER_H
