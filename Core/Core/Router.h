#ifndef VORTEX_CORE_FRAMEWORK_ROUTER_H
#define VORTEX_CORE_FRAMEWORK_ROUTER_H

#include <string>
#include <vector>
#include <map>

namespace Vortex {
	namespace Core {
		class Framework;

		class Router {
		private:
			Framework* framework_;

			std::string request_uri_;
			std::string lang_;
			std::string controller_;
			std::vector<std::string> args_;
			std::map<std::string, std::string> cookies_;
			bool cookies_initialized_ = false;

		public:
			Router(Framework* framework);

			void setup();
			std::string get_hostname();
			std::string get_lang();
			std::string get_controller();
			std::vector<std::string> get_args();
			
			std::string get_post() const;

			std::map<std::string, std::string> get_cookies();
			std::string get_cookie(const std::string& cookie_name, bool* cookie_exists = nullptr);
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_ROUTER_H
