#include <Core/VortexBase.hpp>

using namespace Vortex::Core::Applications;

namespace VortexBase {

    ApplicationRuntime::ApplicationRuntime(
        const std::shared_ptr<Vortex::Core::Modules::DependencyInjector>& di,
        const std::shared_ptr<string_body_request>& request,
        const std::shared_ptr<string_body_response>& response)
        : _app_di(di->di_scope()) {}

    void ApplicationRuntime::run() {

    }

    string_body_request& ApplicationRuntime::request() {
        return *_request;
    }

    string_body_response& ApplicationRuntime::response() {
        return *_response;
    }


    std::shared_ptr<IApplicationRuntime> ApplicationResolver::get_application_runtime(
        const std::shared_ptr<Vortex::Core::Modules::DependencyInjector>& di,
        const std::shared_ptr<string_body_request>& request,
        const std::shared_ptr<string_body_response>& response) {


        return (std::shared_ptr<IApplicationRuntime>)std::make_shared<ApplicationRuntime>(di, request, response);
    }

}  // namespace VortexBase
