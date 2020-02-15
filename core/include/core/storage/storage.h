#ifndef VORTEX_CORE_STORAGE_STORAGE_H
#define VORTEX_CORE_STORAGE_STORAGE_H

#include <string>
#include <maze/object.h>

namespace vortex {
namespace core {
namespace framework {
class Framework;
}

namespace storage {

class Storage {
private:
  framework::Framework* framework_;
  std::string backend_;

public:
  Storage(framework::Framework* framework);

  const std::string get_backend();
};

}  // namespace storage
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_STORAGE_STORAGE_H
