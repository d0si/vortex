#include <core/framework/router.h>
#include <core/framework/framework.h>

namespace vortex {
namespace core {
namespace framework {

host::host(framework* framework) : framework_(framework) {
}

void host::find(std::string hostname) {
}

std::string host::get_id() {
    return "";
}

std::string host::get_host() {
    return "";
}

std::string host::get_app() {
    return "";
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
