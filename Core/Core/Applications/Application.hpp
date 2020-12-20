#pragma once

#include <string>
#include <memory>
#include <Maze/Maze.hpp>
#include <boost/beast/http.hpp>
#include <Core/DLLSupport.hpp>

namespace Vortex::Core::Modules {
    class DependencyInjector;
}

namespace Vortex::Core::Applications {

    typedef boost::beast::http::request<boost::beast::http::string_body> string_body_request;
    typedef boost::beast::http::response<boost::beast::http::string_body> string_body_response;

    class IApplicationRuntime;
    class IRouter;

    class IApplicationResolver {
    public:
        VORTEX_CORE_API IApplicationResolver(
            const std::shared_ptr<Modules::DependencyInjector>& di,
            const std::shared_ptr<string_body_request>& request,
            const std::shared_ptr<string_body_response>& response,
            const Maze::Element& config);
        VORTEX_CORE_API virtual ~IApplicationResolver() = default;

        VORTEX_CORE_API virtual std::shared_ptr<IApplicationRuntime> get_application_runtime() = 0;

    protected:
        std::shared_ptr<Modules::DependencyInjector> _di;
        std::shared_ptr<string_body_request> _request;
        std::shared_ptr<string_body_response> _response;
        Maze::Element _config;

        VORTEX_CORE_API virtual Maze::Element find_host_info(const std::string& hostname) = 0;
        VORTEX_CORE_API virtual Maze::Element find_application_info(const std::string& identifier) = 0;
    };


    class BaseApplicationResolver : public IApplicationResolver {
    public:
        VORTEX_CORE_API BaseApplicationResolver(
            const std::shared_ptr<Vortex::Core::Modules::DependencyInjector>& di,
            const std::shared_ptr<string_body_request>& request,
            const std::shared_ptr<string_body_response>& response,
            const Maze::Element& config);

        VORTEX_CORE_API virtual std::shared_ptr<IApplicationRuntime> get_application_runtime() override;

    protected:
        VORTEX_CORE_API virtual Maze::Element find_host_info(const std::string& hostname) override;
        VORTEX_CORE_API virtual Maze::Element find_application_info(const std::string& identifier) override;
    };


    class IApplicationRuntime : public std::enable_shared_from_this<IApplicationRuntime> {
    public:
        VORTEX_CORE_API IApplicationRuntime(
            const std::shared_ptr<Modules::DependencyInjector>& di,
            const std::shared_ptr<string_body_request>& request,
            const std::shared_ptr<string_body_response>& response,
            const Maze::Element& host_info,
            const Maze::Element& app_info,
            const Maze::Element& config);
        VORTEX_CORE_API virtual ~IApplicationRuntime() = default;

        VORTEX_CORE_API virtual void run() = 0;

        VORTEX_CORE_API virtual string_body_request& request() = 0;
        VORTEX_CORE_API virtual string_body_response& response() = 0;

        VORTEX_CORE_API virtual const Maze::Element& host_info() = 0;
        VORTEX_CORE_API virtual const Maze::Element& app_info() = 0;
        VORTEX_CORE_API virtual const Maze::Element& config() = 0;

        VORTEX_CORE_API virtual IRouter& router() = 0;

    protected:
        std::shared_ptr<Modules::DependencyInjector> _di;
        
        std::shared_ptr<string_body_request> _request;
        std::shared_ptr<string_body_response> _response;

        Maze::Element _host_info;
        Maze::Element _app_info;
        Maze::Element _config;
    };

}  // namespace Vortex::Core::Applications
