#include <core/storage/storage.h>
#include <core/framework/framework.h>

namespace vortex {
namespace core {
namespace storage {

Storage::Storage(framework::Framework* framework) : framework_(framework) {
  this->backend_ = "mongo";

  if (this->framework_->get_config().is_object("storage")) {
    maze::object storage_config = this->framework_->get_config()["storage"].get_object();

    if (storage_config.is_string("backend")) {
      this->backend_ = storage_config["backend"].get_string();
    }
  }
}

const std::string Storage::get_backend() {
  return this->backend_;
}

}  // namespace storage
}  // namespace core
}  // namespace vortex