#ifndef VORTEX_CORE_FRAMEWORK_HOST_H
#define VORTEX_CORE_FRAMEWORK_HOST_H

#include <string>
#include <maze/object.h>

namespace vortex {
namespace core {
namespace framework {

class framework;

class host {
 private:
  framework* framework_;
  maze::object host_;

 public:
  host(framework* framework);

  void find(std::string hostname);

  std::string get_id();
  std::string get_hostname();
  std::string get_app_id();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_HOST_H
