#include <Core/VortexModule/Framework.h>
#include <Core/Exceptions/ExitFrameworkException.h>
#include <Core/VortexModule/Router.h>
#include <Core/VortexModule/Host.h>
#include <Core/VortexModule/Application.h>
#include <Core/VortexModule/Controller.h>
#include <Core/VortexModule/View.h>
#include <Core/VortexModule/Script/Script.h>

namespace Vortex::Core::VortexModule {

    Framework::Framework(
        const Maze::Element& config,
        std::string client_ip,
        boost::beast::http::request<boost::beast::http::string_body>* request,
        boost::beast::http::response<boost::beast::http::string_body>* response)
        : _config(config), _client_ip(client_ip), _request(request), _response(response),
        _router(new Router(this)), _host(new Host(this)),
        _application(new Application(this)), _controller(new Controller(this)),
        _view(new View(this)), _script(new Script::Script(this)) {}

    Framework::~Framework() {
        delete _router;
        delete _host;
        delete _application;
        delete _controller;
        delete _view;
        delete _script;
    }

    void Framework::init() {
        _host->init(_router->hostname());

        _script->init();

        _application->init(_host->application_id());

        _config.apply(_application->config());
        _config.apply(_host->config());

        _router->init();

        _controller->init(
            _application->id(),
            _router->controller(),
            _request->method_string().to_string());
    }

    void Framework::run() {
        _script->exec(_application->script());
        _script->exec(_host->script());
        _script->exec(_controller->script());

        _script->exec(_application->post_script());
        _script->exec(_host->post_script());
        _script->exec(_controller->post_script());

        _view->output();

        throw Exceptions::ExitFrameworkException();
    }

    void Framework::exit() {
        _view->respond();

        throw Exceptions::ExitFrameworkException();
    }

    const std::string& Framework::client_ip() const {
        return _client_ip;
    }

    boost::beast::http::request<boost::beast::http::string_body>* Framework::request() {
        return _request;
    }

    boost::beast::http::response<boost::beast::http::string_body>* Framework::response() {
        return _response;
    }

    Maze::Element* Framework::config() {
        return &_config;
    }

    RouterInterface* Framework::router() {
        return _router;
    }

    HostInterface* Framework::host() {
        return _host;
    }

    ApplicationInterface* Framework::application() {
        return _application;
    }

    ControllerInterface* Framework::controller() {
        return _controller;
    }

    ViewInterface* Framework::view() {
        return _view;
    }

    ScriptInterface* Framework::script() {
        return _script;
    }

}
