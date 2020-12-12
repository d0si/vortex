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
		VORTEX_CORE_API Framework(
			const Maze::Element& config,
			std::string client_ip,
			boost::beast::http::request<boost::beast::http::string_body>* request,
			boost::beast::http::response<boost::beast::http::string_body>* response);

		VORTEX_CORE_API void setup();
		VORTEX_CORE_API void run();
		VORTEX_CORE_API void exit();

		VORTEX_CORE_API const std::string& client_ip() const;
		VORTEX_CORE_API boost::beast::http::request<boost::beast::http::string_body>* request();
		VORTEX_CORE_API boost::beast::http::response<boost::beast::http::string_body>* response();
		VORTEX_CORE_API Maze::Element* config();
		VORTEX_CORE_API Router* router();
		VORTEX_CORE_API Host* host();
		VORTEX_CORE_API Application* application();
		VORTEX_CORE_API Controller* controller();
		VORTEX_CORE_API View* view();
		VORTEX_CORE_API Script::Script* script();

	private:
		std::string _client_ip;
		boost::beast::http::request<boost::beast::http::string_body>* _request;
		boost::beast::http::response<boost::beast::http::string_body>* _response;
		Maze::Element _config;

		Router _router;
		Host _host;
		Application _application;
		Controller _controller;
		View _view;
		Script::Script _script;
	};

}  // namespace Vortex::Core
