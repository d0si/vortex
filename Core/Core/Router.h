#pragma once

#include <string>
#include <vector>
#include <map>
#include <Core/DLLSupport.h>

namespace Vortex::Core {

	class Framework;


	class Router {
	public:
		VORTEX_CORE_API Router(Framework* framework);

		VORTEX_CORE_API void setup();
		VORTEX_CORE_API std::string get_hostname();
		VORTEX_CORE_API std::string get_lang();
		VORTEX_CORE_API std::string get_controller();
		VORTEX_CORE_API std::vector<std::string> get_args();

		VORTEX_CORE_API std::string get_post() const;

		VORTEX_CORE_API std::map<std::string, std::string> get_cookies();
		VORTEX_CORE_API std::string get_cookie(const std::string& cookie_name, bool* cookie_exists = nullptr);

	private:
		Framework* _framework;

		std::string _request_uri;
		std::string _lang;
		std::string _controller;
		std::vector<std::string> _args;
		std::map<std::string, std::string> _cookies;
		bool _cookies_initialized = false;
	};

}  // namespace Vortex::Core
