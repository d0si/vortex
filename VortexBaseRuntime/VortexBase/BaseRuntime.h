#pragma once

#include <string>
#include <boost/beast/http.hpp>
#include <Maze/Maze.hpp>
#include <Core/DLLSupport.h>
#include <Core/Interfaces.h>

namespace VortexBase {

	class BaseRuntime : public Vortex::Core::RuntimeInterface {
	public:
		VORTEX_CORE_API BaseRuntime(
			Vortex::Core::Modules::DependencyInjector* di,
			const Maze::Element& config,
			std::string client_ip,
			boost::beast::http::request<boost::beast::http::string_body>* request,
			boost::beast::http::response<boost::beast::http::string_body>* response);
		VORTEX_CORE_API virtual ~BaseRuntime() override;

		VORTEX_CORE_API virtual void init() override;
		VORTEX_CORE_API virtual void run() override;
		VORTEX_CORE_API virtual void exit() override;

		VORTEX_CORE_API virtual const std::string& client_ip() const override;
		VORTEX_CORE_API virtual boost::beast::http::request<boost::beast::http::string_body>* request() override;
		VORTEX_CORE_API virtual boost::beast::http::response<boost::beast::http::string_body>* response() override;
		VORTEX_CORE_API virtual Maze::Element* config() override;
		VORTEX_CORE_API virtual Vortex::Core::RouterInterface* router() override;
		VORTEX_CORE_API virtual Vortex::Core::HostInterface* host() override;
		VORTEX_CORE_API virtual Vortex::Core::ApplicationInterface* application() override;
		VORTEX_CORE_API virtual Vortex::Core::ControllerInterface* controller() override;
		VORTEX_CORE_API virtual Vortex::Core::ViewInterface* view() override;
		VORTEX_CORE_API virtual Vortex::Core::ScriptInterface* script() override;

		VORTEX_CORE_API virtual Vortex::Core::Modules::DependencyInjector* di() override;

	private:
		std::string _client_ip;
		boost::beast::http::request<boost::beast::http::string_body>* _request;
		boost::beast::http::response<boost::beast::http::string_body>* _response;
		Maze::Element _config;

		Vortex::Core::RouterInterface* _router;
		Vortex::Core::HostInterface* _host;
		Vortex::Core::ApplicationInterface* _application;
		Vortex::Core::ControllerInterface* _controller;
		Vortex::Core::ViewInterface* _view;
		Vortex::Core::ScriptInterface* _script;
	};

}  // namespace VortexBase
