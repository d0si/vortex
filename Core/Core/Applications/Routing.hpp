#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <Core/DLLSupport.hpp>

namespace Vortex::Core::Applications {
    
    class IApplicationRuntime;

    class IRouter {
    public:
        VORTEX_CORE_API IRouter(const std::shared_ptr<IApplicationRuntime>& runtime);
        VORTEX_CORE_API virtual ~IRouter() = default;

        VORTEX_CORE_API virtual void init() = 0;

        VORTEX_CORE_API virtual std::string hostname() = 0;
        VORTEX_CORE_API virtual std::string lang() = 0;
        VORTEX_CORE_API virtual std::string controller() = 0;
        VORTEX_CORE_API virtual std::vector<std::string> args() = 0;

        VORTEX_CORE_API virtual std::string request_post_body() = 0;

        VORTEX_CORE_API virtual std::map<std::string, std::string> cookies() = 0;
        VORTEX_CORE_API virtual std::string cookie(const std::string& cookie_name, bool* out_cookie_exists = nullptr) = 0;

    protected:
        std::shared_ptr<IApplicationRuntime> _runtime;
    };


    class BaseRouter : public IRouter {
    public:
        VORTEX_CORE_API BaseRouter(const std::shared_ptr<IApplicationRuntime>& runtime);

        VORTEX_CORE_API virtual void init() override;

        VORTEX_CORE_API virtual std::string hostname() override;
        VORTEX_CORE_API virtual std::string lang() override;
        VORTEX_CORE_API virtual std::string controller() override;
        VORTEX_CORE_API virtual std::vector<std::string> args() override;

        VORTEX_CORE_API virtual std::string request_post_body() override;

        VORTEX_CORE_API virtual std::map<std::string, std::string> cookies() override;
        VORTEX_CORE_API virtual std::string cookie(const std::string& cookie_name, bool* out_cookie_exists = nullptr) override;

    protected:
        std::string _request_uri;
        std::string _lang;
        std::string _controller;
        std::vector<std::string> _args;
        std::map<std::string, std::string> _cookies;
        bool _cookies_initialized = false;
    };

}  // namespace Vortex::Core::Applications
