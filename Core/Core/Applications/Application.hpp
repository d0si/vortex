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

    class IApplicationResolver {
    public:
        VORTEX_CORE_API IApplicationResolver(
            const std::shared_ptr<Vortex::Core::Modules::DependencyInjector>& di,
            const std::shared_ptr<string_body_request>& request,
            const std::shared_ptr<string_body_response>& response);
        VORTEX_CORE_API virtual ~IApplicationResolver() = default;

        VORTEX_CORE_API virtual std::shared_ptr<IApplicationRuntime> get_application_runtime() = 0;

    protected:
        std::shared_ptr<Vortex::Core::Modules::DependencyInjector> _di;
        std::shared_ptr<string_body_request> _request;
        std::shared_ptr<string_body_response> _response;

        VORTEX_CORE_API virtual Maze::Element find_host_info(const std::string& hostname) = 0;
        VORTEX_CORE_API virtual Maze::Element find_application_info(const std::string& identifier) = 0;
    };


    class IApplicationRuntime {
    public:
        VORTEX_CORE_API virtual ~IApplicationRuntime() = default;

        VORTEX_CORE_API virtual void run() = 0;

        VORTEX_CORE_API virtual string_body_request& request() = 0;
        VORTEX_CORE_API virtual string_body_response& response() = 0;
    };

}  // namespace Vortex::Core::Applications
