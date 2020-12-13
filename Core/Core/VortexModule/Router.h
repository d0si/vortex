#pragma once

#include <Core/Interfaces.h>

namespace Vortex::Core::VortexModule {

	class Router : public RouterInterface {
	public:
		VORTEX_CORE_API Router(FrameworkInterface* framework);
		VORTEX_CORE_API virtual ~Router() override = default;

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

}  // namespace Vortex::Core::VortexModule
