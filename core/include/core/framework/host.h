#ifndef VORTEX_CORE_FRAMEWORK_HOST_H
#define VORTEX_CORE_FRAMEWORK_HOST_H

#include <string>

namespace vortex {
namespace core {
namespace framework {

class Framework;

class Host {
 private:
  Framework* framework_;

 public:
  Host(Framework* framework);

  void find(std::string hostname);

  std::string getId();
  std::string getHost();
  std::string getApp();
};

}  // namespace framework
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_FRAMEWORK_HOST_H
