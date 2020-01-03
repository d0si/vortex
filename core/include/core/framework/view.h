#ifndef VORTEX_CORE_FRAMEWORK_VIEW_H
#define VORTEX_CORE_FRAMEWORK_VIEW_H

#include <string>

namespace vortex {
namespace core {
namespace framework {

class framework;

class view {
 private:
  framework* framework_;

  std::string rendered_;

 public:
  view(framework* framework);

  void output();
  void respond();
  void echo(std::string contents);
  void clear();
  void parse(std::string code);
  void finish();

  void set_template(std::string name);
  void parse_template();

  void set_page(std::string name);
  void parse_page();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_VIEW_H
