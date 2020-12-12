#include <Core/Framework.h>
#include <Core/Exceptions/ExitFrameworkException.h>

namespace Vortex::Core {

    Framework::Framework(
        const Maze::Element& config,
        std::string client_ip,
        boost::beast::http::request<boost::beast::http::string_body>* request,
        boost::beast::http::response<boost::beast::http::string_body>* response)
        : _config(config), _client_ip(client_ip),
        _request(request), _response(response),
        _router(this), _host(this),
        _application(this), _controller(this),
        _view(this), _script(this) {}

    void Framework::setup() {
        _host.find(_router.get_hostname());

        _script.setup();

        _application.find(_host.get_app_id());

        _config.apply(_application.get_config());
        _config.apply(_host.get_config());

        _router.setup();

        _controller.find(
            _application.get_id(),
            _router.get_controller(),
            _request->method_string().to_string());
    }

    void Framework::run() {
        _script.exec(_application.get_script());
        _script.exec(_host.get_script());
        _script.exec(_controller.get_script());

        _script.exec(_application.get_post_script());
        _script.exec(_host.get_post_script());
        _script.exec(_controller.get_post_script());

        _view.output();

        throw Exceptions::ExitFrameworkException();
    }

    void Framework::exit() {
        _view.respond();

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

    Router* Framework::router() {
        return &_router;
    }

    Host* Framework::host() {
        return &_host;
    }

    Application* Framework::application() {
        return &_application;
    }

    Controller* Framework::controller() {
        return &_controller;
    }

    View* Framework::view() {
        return &_view;
    }

    Script::Script* Framework::script() {
        return &_script;
    }

}
