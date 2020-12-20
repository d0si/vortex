#include <Core/Applications/Routing.hpp>
#include <Core/Applications/Application.hpp>

namespace Vortex::Core::Applications {

    IRouter::IRouter(const std::shared_ptr<IApplicationRuntime>& runtime)
        : _runtime(runtime) {
    
    }


    BaseRouter::BaseRouter(const std::shared_ptr<IApplicationRuntime>& runtime)
        : IRouter(runtime) {}
    
    void BaseRouter::init() {
        std::string target = _runtime->request().target().to_string();
        _request_uri = target.substr(1, target.length() - 1);


        Maze::Element router_config = _runtime->config().get("router", Maze::Type::Object);

        if (router_config.is_object("routes")) {
            Maze::Element routes = router_config.get("routes", Maze::Type::Object);

            for (auto it = routes.keys_begin(); it != routes.keys_end(); ++it) {
                const std::string& route_url = *it;
                const Maze::Element& route = routes.get(route_url);

                if (route.is_object() &&
                    _request_uri.substr(0, route_url.length()) == route_url) {

                    if (route.is_string("default_lang")) {
                        _lang = route.get("default_lang").s();
                    }
                    if (route.is_string("default_controller")) {
                        _controller = route.get("default_controller").s();
                    }
                    if (route.is_array("url_schemes")) {
                        router_config.set("url_schemes", route.get("url_schemes"));
                    }
                }
            }
        }

        if (!router_config.is_array("url_schemes")) {
            router_config.set("url_schemes", Maze::Element({
                "lang",
                Maze::Element({"type", "default_value"}, {"controller", "index"}),
                "controller",
                "args"
                }));
        }

        std::vector<std::string> request_uri_parts;
        std::string request_uri_part;
        for (const char& it : _request_uri) {
            if (it == '/') {
                request_uri_parts.push_back(request_uri_part);
                request_uri_part = "";
            }
            else if (it == '?') {
                break;
            }
            else if (it == '#') {
                break;
            }
            else {
                request_uri_part += it;
            }
        }
        if (request_uri_part.length() > 0) {
            request_uri_parts.push_back(request_uri_part);
        }

        int i = 0;
        int parts_count = (int)request_uri_parts.size();

        std::vector<std::string> controller_parts;
        Maze::Element url_schemes = router_config.get("url_schemes", Maze::Type::Array);
        for (auto url_scheme = url_schemes.begin(); url_scheme != url_schemes.end(); url_scheme++) {
            if (url_scheme->is_string()) {
                std::string type = url_scheme->get_string();

                if (type == "lang" && i < parts_count) {
                    _lang = request_uri_parts[i];
                }
                else if (type == "controller" && i < parts_count) {
                    controller_parts.push_back(request_uri_parts[i]);
                }
                else if (type == "args" && i < parts_count) {
                    for (; i < parts_count; i++) {
                        _args.push_back(request_uri_parts[i]);
                    }
                }
                else if (type == "arg" && i < parts_count) {
                    _args.push_back(request_uri_parts[i]);
                }
            }
            else if (url_scheme->is_object()) {
                if (url_scheme->is_string("type")) {
                    std::string type = url_scheme->get("type").s();

                    if (type == "lang") {
                        if (url_scheme->is_string("value")) {
                            _lang = url_scheme->get("value").s();
                        }
                        else if (i < parts_count) {
                            std::string lang;

                            if (url_scheme->is_string("prefix")) {
                                lang += url_scheme->get("prefix").s();
                            }

                            lang += request_uri_parts[i];

                            if (url_scheme->is_string("suffix")) {
                                lang += url_scheme->get("suffix").s();
                            }

                            _lang = lang;
                        }
                        else if (url_scheme->is_string("default_value")) {
                            _lang = url_scheme->get("default_value").s();
                        }
                    }
                    else if (type == "controller") {
                        if (url_scheme->is_string("value")) {
                            controller_parts.push_back(url_scheme->get("value").s());
                        }
                        else if (i < parts_count) {
                            std::string controller;

                            if (url_scheme->is_string("prefix")) {
                                controller += url_scheme->get("prefix").s();
                            }

                            controller += request_uri_parts[i];

                            if (url_scheme->is_string("suffix")) {
                                controller += url_scheme->get("suffix").s();
                            }

                            controller_parts.push_back(controller);
                        }
                        else if (url_scheme->is_string("default_value")) {
                            controller_parts.push_back(url_scheme->get("default_value").s());
                        }
                    }
                    else if (type == "args") {
                        if (i < parts_count) {
                            if (url_scheme->is_int("count")) {
                                int arg_count = url_scheme->get("count").i();

                                for (int ix = 0; ix < arg_count; ++ix) {
                                    if (i < parts_count) {
                                        _args.push_back(request_uri_parts[i]);
                                        i++;
                                    }
                                }
                            }
                            else {
                                for (; i < parts_count; ++i) {
                                    _args.push_back(request_uri_parts[i]);
                                }
                            }
                        }
                    }
                    else if (type == "arg") {
                        if (url_scheme->is_string("value")) {
                            _args.push_back(url_scheme->get("value").s());
                        }
                        else if (i < parts_count) {
                            std::string arg;

                            if (url_scheme->is_string("prefix")) {
                                arg += url_scheme->get("prefix").s();
                            }

                            arg += request_uri_parts[i];

                            if (url_scheme->is_string("suffix")) {
                                arg += url_scheme->get("suffix").s();
                            }

                            _args.push_back(arg);
                        }
                        else if (url_scheme->is_string("default_value")) {
                            _args.push_back(url_scheme->get("default_value").s());
                        }
                    }
                }
            }

            i++;
        }

        if (controller_parts.size() > 0) {
            std::string controller_str;

            for (int i = 0; i < controller_parts.size(); ++i) {
                controller_str += controller_parts[i] + "/";
            }
            controller_str.erase(controller_str.length() - 1);

            _controller = controller_str;
        }
    }

    std::string BaseRouter::hostname() {
        return _runtime->request().base()[boost::beast::http::field::host].to_string();
    }

    std::string BaseRouter::lang() {
        return _lang;
    }

    std::string BaseRouter::controller() {
        return _controller;
    }

    std::vector<std::string> BaseRouter::args() {
        return _args;
    }

    std::string BaseRouter::request_post_body() {
        return _runtime->request().body();
    }

    std::map<std::string, std::string> BaseRouter::cookies() {
        if (!_cookies_initialized) {
            std::string cookies_string = _runtime->request().base()[boost::beast::http::field::cookie].to_string();

            std::string key = "";
            std::string value = "";
            bool grabbing_value_part = false;

            for (unsigned int i = 0; i < cookies_string.length(); ++i) {
                char val = cookies_string[i];

                if (val == ';') {
                    _cookies.emplace(std::make_pair(key, value));
                    key.clear();
                    value.clear();
                    grabbing_value_part = false;

                    while (cookies_string[i + 1] == ' ') {
                        ++i;
                    }
                }
                else if (val == '=') {
                    grabbing_value_part = true;
                }
                else {
                    if (!grabbing_value_part) {
                        key += val;
                    }
                    else {
                        value += val;
                    }
                }
            }

            if (!key.empty()) {
                _cookies.emplace(std::make_pair(key, value));
            }
        }

        return _cookies;
    }

    std::string BaseRouter::cookie(const std::string& cookie_name, bool* out_cookie_exists) {
        const auto& cookies = this->cookies();

        const auto& it = cookies.find(cookie_name);
        if (it != cookies.end()) {
            if (out_cookie_exists != nullptr) {
                *out_cookie_exists = true;
            }

            return it->second;
        }

        if (out_cookie_exists != nullptr) {
            *out_cookie_exists = false;
        }

        return "";
    }
}
