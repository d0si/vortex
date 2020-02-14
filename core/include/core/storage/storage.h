#ifndef VORTEX_CORE_STORAGE_STORAGE_H
#define VORTEX_CORE_STORAGE_STORAGE_H

namespace vortex {
namespace core {
namespace framework {
class framework;
}

namespace storage {

class storage {
private:
  framework::framework* framework_;

public:
  storage(framework::framework* framework);
};

}  // namespace storage
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_STORAGE_STORAGE_H
