#ifndef VORTEX_CORE_FRAMEWORK_FRAMEWORK_H
#define VORTEX_CORE_FRAMEWORK_FRAMEWORK_H

#include <string>
#include <boost/beast/http.hpp>
#include <maze/object.h>
#include <Core/Router.h>
#include <Core/Host.h>
#include <Core/Application.h>
#include <Core/Controller.h>
#include <Core/View.h>
#include <Core/Cache/Redis.h>
#include <Core/Script/Script.h>

namespace Vortex {
	namespace Core {
		class Framework {
		public:
			std::string client_ip_;
			boost::beast::http::request<boost::beast::http::string_body>* request_;
			boost::beast::http::response<boost::beast::http::string_body>* response_;
			maze::object config_;
			Cache::Redis* redis_;

			Router router_;
			Host host_;
			Application application_;
			Controller controller_;
			View view_;
			Script::Script script_;

			Framework(
				maze::object config,
				Cache::Redis* redis,
				std::string client_ip,
				boost::beast::http::request<boost::beast::http::string_body>* request,
				boost::beast::http::response<boost::beast::http::string_body>* response);

			void setup();
			void run();
			void exit();

			maze::object get_config();
		};
	}  // namespace Core
}  // namespace Vortex

#endif  // VORTEX_CORE_FRAMEWORK_FRAMEWORK_H
