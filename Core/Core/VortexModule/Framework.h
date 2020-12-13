#pragma once

#include <string>
#include <boost/beast/http.hpp>
#include <Maze/Maze.hpp>
#include <Core/DLLSupport.h>
#include <Core/Interfaces.h>

namespace Vortex::Core::VortexModule {

	class Framework : public FrameworkInterface {
	public:
		VORTEX_CORE_API Framework(
			const Maze::Element& config,
			std::string client_ip,
			boost::beast::http::request<boost::beast::http::string_body>* request,
			boost::beast::http::response<boost::beast::http::string_body>* response);
		VORTEX_CORE_API virtual ~Framework() override;

		VORTEX_CORE_API virtual void init() override;
		VORTEX_CORE_API virtual void run() override;
		VORTEX_CORE_API virtual void exit() override;

		VORTEX_CORE_API virtual const std::string& client_ip() const override;
		VORTEX_CORE_API virtual boost::beast::http::request<boost::beast::http::string_body>* request() override;
		VORTEX_CORE_API virtual boost::beast::http::response<boost::beast::http::string_body>* response() override;
		VORTEX_CORE_API virtual Maze::Element* config() override;
		VORTEX_CORE_API virtual RouterInterface* router() override;
		VORTEX_CORE_API virtual HostInterface* host() override;
		VORTEX_CORE_API virtual ApplicationInterface* application() override;
		VORTEX_CORE_API virtual ControllerInterface* controller() override;
		VORTEX_CORE_API virtual ViewInterface* view() override;
		VORTEX_CORE_API virtual ScriptInterface* script() override;

	private:
		std::string _client_ip;
		boost::beast::http::request<boost::beast::http::string_body>* _request;
		boost::beast::http::response<boost::beast::http::string_body>* _response;
		Maze::Element _config;

		RouterInterface* _router;
		HostInterface* _host;
		ApplicationInterface* _application;
		ControllerInterface* _controller;
		ViewInterface* _view;
		ScriptInterface* _script;
	};

}  // namespace Vortex::Core::VortexModule
