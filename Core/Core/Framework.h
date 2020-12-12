#pragma once

#include <string>
#include <boost/beast/http.hpp>
#include <Maze/Maze.hpp>
#include <Core/DLLSupport.h>
#include <Core/Router.h>
#include <Core/Host.h>
#include <Core/Application.h>
#include <Core/Controller.h>
#include <Core/View.h>
#include <Core/Script/Script.h>

namespace Vortex::Core {

	class Framework {
	public:
		std::string client_ip_;
		boost::beast::http::request<boost::beast::http::string_body>* request_;
		boost::beast::http::response<boost::beast::http::string_body>* response_;
		Maze::Element config_;

		Router router_;
		Host host_;
		Application application_;
		Controller controller_;
		View view_;
		Script::Script script_;

		VORTEX_CORE_API Framework(
			const Maze::Element& config,
			std::string client_ip,
			boost::beast::http::request<boost::beast::http::string_body>* request,
			boost::beast::http::response<boost::beast::http::string_body>* response);

		VORTEX_CORE_API void setup();
		VORTEX_CORE_API void run();
		VORTEX_CORE_API void exit();

		VORTEX_CORE_API const Maze::Element& get_config() const;
	};

}  // namespace Vortex::Core
