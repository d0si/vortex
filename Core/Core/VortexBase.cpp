#include <Core/VortexBase.hpp>
#include <Core/GlobalRuntime.hpp>

using namespace Vortex::Core::Applications;
using Vortex::Core::GlobalRuntime;

#ifndef FALLBACK_VORTEX_HOST_ID
#define FALLBACK_VORTEX_HOST_ID "5fdceeb02a7af2799c4efd2d"
#endif

#ifndef FALLBACK_VORTEX_APPLICATION_ID
#define FALLBACK_VORTEX_APPLICATION_ID "5fdcee7369e2f923a3406417"
#endif

namespace VortexBase {

    ApplicationRuntime::ApplicationRuntime(
        const std::shared_ptr<Vortex::Core::Modules::DependencyInjector>& di,
        const std::shared_ptr<string_body_request>& request,
        const std::shared_ptr<string_body_response>& response,
        const Maze::Element& host_info,
        const Maze::Element& app_info,
        const Maze::Element& config)
        : IApplicationRuntime(di, request, response, host_info, app_info, config),
        _router(di->activate_router(shared_from_this())) {}

    void ApplicationRuntime::run() {

    }

    string_body_request& ApplicationRuntime::request() {
        return *_request;
    }

    string_body_response& ApplicationRuntime::response() {
        return *_response;
    }

    const Maze::Element& ApplicationRuntime::host_info() {
        return _host_info;
    }

    const Maze::Element& ApplicationRuntime::app_info() {
        return _app_info;
    }

    const Maze::Element& ApplicationRuntime::config() {
        return _config;
    }

    IRouter& ApplicationRuntime::router() {
        return *_router;
    }

}  // namespace VortexBase
