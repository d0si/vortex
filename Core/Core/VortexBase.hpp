#pragma once

#include <Core/Applications/Application.hpp>
#include <Core/Modules/DependencyInjection.hpp>

using namespace Vortex::Core::Applications;

namespace VortexBase {

    class ApplicationResolver : public IApplicationResolver {
    public:
        VORTEX_CORE_API ApplicationResolver(
            const std::shared_ptr<Vortex::Core::Modules::DependencyInjector>& di,
            const std::shared_ptr<string_body_request>& request,
            const std::shared_ptr<string_body_response>& response);

        VORTEX_CORE_API virtual std::shared_ptr<IApplicationRuntime> get_application_runtime();

    protected:
        VORTEX_CORE_API virtual Maze::Element find_host_info(const std::string& hostname) override;
        VORTEX_CORE_API virtual Maze::Element find_application_info(const std::string& identifier) override;
    };


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

}  // namespace VortexBase
