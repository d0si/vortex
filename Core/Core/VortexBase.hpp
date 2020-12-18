#pragma once

#include <Core/Applications/Application.hpp>
#include <Core/Modules/DependencyInjection.hpp>

using namespace Vortex::Core::Applications;

namespace VortexBase {

    class ApplicationRuntime : public IApplicationRuntime {
    public:
        VORTEX_CORE_API ApplicationRuntime(
            const std::shared_ptr<Vortex::Core::Modules::DependencyInjector>& di,
            const std::shared_ptr<string_body_request>& request,
            const std::shared_ptr<string_body_response>& response);

        VORTEX_CORE_API virtual void run() override;

        VORTEX_CORE_API virtual string_body_request& request() override;
        VORTEX_CORE_API virtual string_body_response& response() override;

    protected:
        std::shared_ptr<Vortex::Core::Modules::DependencyInjector> _app_di;
        std::shared_ptr<string_body_request> _request;
        std::shared_ptr<string_body_response> _response;
    };


    class ApplicationResolver : public IApplicationResolver {
    public:
        VORTEX_CORE_API virtual std::shared_ptr<IApplicationRuntime> get_application_runtime(
            const std::shared_ptr<Vortex::Core::Modules::DependencyInjector>& di,
            const std::shared_ptr<string_body_request>& request,
            const std::shared_ptr<string_body_response>& response);
    };

}  // namespace VortexBase
