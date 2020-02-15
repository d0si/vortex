#ifndef VORTEX_CORE_FRAMEWORK_VIEW_H
#define VORTEX_CORE_FRAMEWORK_VIEW_H

#include <string>
#include <maze/object.h>

namespace vortex {
namespace core {
namespace framework {

class Framework;

class View {
 private:
  Framework* framework_;

  std::string rendered_;
  maze::object template_;
  maze::object page_;

 public:
  View(Framework* framework);

  void output();
  void respond();
  void echo(std::string contents);
  void clear();
  void finish();
  std::string parse(std::string code);

  void set_template(std::string name);
  std::string parse_template();

  void set_page(std::string name);
  std::string parse_page();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_VIEW_H
