#include <core/framework/router.h>
#include <core/framework/framework.h>

namespace vortex {
namespace core {
namespace framework {

host::host(framework* framework) : framework_(framework) {
}

void host::find(std::string hostname) {
  host_ = framework_->mongo_
    .get_collection("hosts")
    .find_one(maze::object("hostname", hostname));
}

std::string host::get_id() {
    return host_["_id"].get_object()["$oid"].get_string();
}

std::string host::get_hostname() {
    return host_["hostname"].get_string();
}

std::string host::get_app_id() {
    return host_["app_id"].get_string();
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
