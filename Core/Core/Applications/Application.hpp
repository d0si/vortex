#pragma once

#include <string>
#include <memory>
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
        VORTEX_CORE_API virtual ~IApplicationResolver() = default;

        VORTEX_CORE_API virtual std::shared_ptr<IApplicationRuntime> get_application_runtime(
            const std::shared_ptr<Modules::DependencyInjector>& di,
            const std::shared_ptr<string_body_request>& request,
            const std::shared_ptr<string_body_response>& response) = 0;
    };

    
    class IApplicationRuntime {
    public:
        VORTEX_CORE_API virtual ~IApplicationRuntime() = default;

        VORTEX_CORE_API virtual void run() = 0;

        VORTEX_CORE_API virtual string_body_request& request() = 0;
        VORTEX_CORE_API virtual string_body_response& response() = 0;
    };

}  // namespace Vortex::Core::Applications
