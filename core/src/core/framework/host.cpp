#include "core/framework/router.h"
#include "core/framework/framework.h"

namespace vortex {
namespace core {
namespace framework {

Host::Host(Framework* framework) : framework_(framework) {
}

void Host::find(std::string hostname) {
}

std::string Host::getId() {
    return "";
}

std::string Host::getHost() {
    return "";
}

std::string Host::getApp() {
    return "";
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
