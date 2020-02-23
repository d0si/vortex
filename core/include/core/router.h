#ifndef VORTEX_CORE_FRAMEWORK_ROUTER_H
#define VORTEX_CORE_FRAMEWORK_ROUTER_H

#include <string>
#include <vector>

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

		public:
			Router(Framework* framework);

			void setup();
			std::string get_hostname();
			std::string get_lang();
			std::string get_controller();
			std::vector<std::string> get_args();
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_ROUTER_H
