#pragma once

#include <string>
#include <boost/beast/http.hpp>
#include <Maze/Maze.hpp>
#include <Core/DLLSupport.h>
#include <Core/Interfaces.h>

namespace Vortex::VortexFramework {

	class Framework : public Core::FrameworkInterface {
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
		VORTEX_CORE_API virtual Core::RouterInterface* router() override;
		VORTEX_CORE_API virtual Core::HostInterface* host() override;
		VORTEX_CORE_API virtual Core::ApplicationInterface* application() override;
		VORTEX_CORE_API virtual Core::ControllerInterface* controller() override;
		VORTEX_CORE_API virtual Core::ViewInterface* view() override;
		VORTEX_CORE_API virtual Core::ScriptInterface* script() override;

	private:
		std::string _client_ip;
		boost::beast::http::request<boost::beast::http::string_body>* _request;
		boost::beast::http::response<boost::beast::http::string_body>* _response;
		Maze::Element _config;

		Core::RouterInterface* _router;
		Core::HostInterface* _host;
		Core::ApplicationInterface* _application;
		Core::ControllerInterface* _controller;
		Core::ViewInterface* _view;
		Core::ScriptInterface* _script;
	};

}  // namespace Vortex::VortexFramework
