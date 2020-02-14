#ifndef VORTEX_CORE_STORAGE_STORAGE_H
#define VORTEX_CORE_STORAGE_STORAGE_H

#include <string>
#include <maze/object.h>

namespace vortex {
namespace core {
namespace framework {
class framework;
}

namespace storage {

class storage {
private:
  framework::framework* framework_;
  std::string backend_;

public:
  storage(framework::framework* framework);

  const std::string get_backend();
};

}  // namespace storage
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_STORAGE_STORAGE_H
