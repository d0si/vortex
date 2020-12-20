#pragma once

#include <Maze/Maze.hpp>
#include <Core/DLLSupport.hpp>
#include <Core/Applications/Application.hpp>
#include <Core/Modules/DependencyInjection.hpp>

using namespace Vortex::Core::Applications;

namespace VortexBase {

    /*class ApplicationResolver : public IApplicationResolver {
    public:
        VORTEX_CORE_API ApplicationResolver(
            const std::shared_ptr<Vortex::Core::Modules::DependencyInjector>& di,
            const std::shared_ptr<string_body_request>& request,
            const std::shared_ptr<string_body_response>& response,
            const Maze::Element& config);

        VORTEX_CORE_API virtual std::shared_ptr<IApplicationRuntime> get_application_runtime();

    protected:
        VORTEX_CORE_API virtual Maze::Element find_host_info(const std::string& hostname) override;
        VORTEX_CORE_API virtual Maze::Element find_application_info(const std::string& identifier) override;
    };*/


    class ApplicationRuntime : public IApplicationRuntime {
    public:
        VORTEX_CORE_API ApplicationRuntime(
            const std::shared_ptr<Vortex::Core::Modules::DependencyInjector>& di,
            const std::shared_ptr<string_body_request>& request,
            const std::shared_ptr<string_body_response>& response,
            const Maze::Element& host_info,
            const Maze::Element& app_info,
            const Maze::Element& config);

        VORTEX_CORE_API virtual void run() override;

        VORTEX_CORE_API virtual string_body_request& request() override;
        VORTEX_CORE_API virtual string_body_response& response() override;

        VORTEX_CORE_API virtual const Maze::Element& host_info() override;
        VORTEX_CORE_API virtual const Maze::Element& app_info() override;
        VORTEX_CORE_API virtual const Maze::Element& config() override;

        VORTEX_CORE_API virtual IRouter& router() override;

    protected:
        std::shared_ptr<Vortex::Core::Modules::DependencyInjector> _app_di;

        std::shared_ptr<Vortex::Core::Applications::IRouter> _router;
    };

}  // namespace VortexBase
