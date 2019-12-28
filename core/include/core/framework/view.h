#ifndef VORTEX_CORE_FRAMEWORK_VIEW_H
#define VORTEX_CORE_FRAMEWORK_VIEW_H

#include <string>

namespace vortex {
namespace core {
namespace framework {

class Framework;

class View {
 private:
  Framework* framework_;

  std::string rendered_;

 public:
  View(Framework* framework);

  void output();
  void respond();
  void echo(std::string contents);
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_VIEW_H
