#include <Core/Router.h>
#include <Core/Framework.h>

namespace Vortex {
    namespace Core {
        Router::Router(Framework* framework) : framework_(framework) {
            lang_ = "en";
            controller_ = "index";

            std::string target = framework_->request_->target().to_string();
            request_uri_ = target.substr(1, target.length() - 1);
        }

        void Router::setup() {
            Maze::Element router_config = framework_->config_.get("router", Maze::Type::Object);

            if (router_config.is_object("routes")) {
                Maze::Element routes = router_config.get("routes", Maze::Type::Object);

                for (auto it = routes.keys_begin(); it != routes.keys_end(); ++it) {
                    const std::string& route_url = *it;
                    const Maze::Element& route = routes.get(route_url);

                    if (route.is_object() &&
                        request_uri_.substr(0, route_url.length()) == route_url) {

                        if (route.is_string("default_lang")) {
                            lang_ = route.get("default_lang").s();
                        }
                        if (route.is_string("default_controller")) {
                            controller_ = route.get("default_controller").s();
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
            for (auto it = request_uri_.begin(); it != request_uri_.end(); it++) {
                if (*it == '/') {
                    request_uri_parts.push_back(request_uri_part);
                    request_uri_part = "";
                }
                else if (*it == '?') {
                    break;
                }
                else if (*it == '#') {
                    break;
                }
                else {
                    request_uri_part += *it;
                }
            }
            if (request_uri_part.length() > 0) {
                request_uri_parts.push_back(request_uri_part);
            }

            int i = 0;
            int parts_count = request_uri_parts.size();

            std::vector<std::string> controller_parts;
            Maze::Element url_schemes = router_config.get("url_schemes", Maze::Type::Array);
            for (auto url_scheme = url_schemes.begin(); url_scheme != url_schemes.end(); url_scheme++) {
                if (url_scheme->is_string()) {
                    std::string type = url_scheme->get_string();

                    if (type == "lang" && i < parts_count) {
                        lang_ = request_uri_parts[i];
                    }
                    else if (type == "controller" && i < parts_count) {
                        controller_parts.push_back(request_uri_parts[i]);
                    }
                    else if (type == "args" && i < parts_count) {
                        for (; i < parts_count; i++) {
                            args_.push_back(request_uri_parts[i]);
                        }
                    }
                    else if (type == "arg" && i < parts_count) {
                        args_.push_back(request_uri_parts[i]);
                    }
                }
                else if (url_scheme->is_object()) {
                    if (url_scheme->is_string("type")) {
                        std::string type = url_scheme->get("type").s();

                        if (type == "lang") {
                            if (url_scheme->is_string("value")) {
                                lang_ = url_scheme->get("value").s();
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

                                lang_ = lang;
                            }
                            else if (url_scheme->is_string("default_value")) {
                                lang_ = url_scheme->get("default_value").s();
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
                                            args_.push_back(request_uri_parts[i]);
                                            i++;
                                        }
                                    }
                                }
                                else {
                                    for (; i < parts_count; ++i) {
                                        args_.push_back(request_uri_parts[i]);
                                    }
                                }
                            }
                        }
                        else if (type == "arg") {
                            if (url_scheme->is_string("value")) {
                                args_.push_back(url_scheme->get("value").s());
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

                                args_.push_back(arg);
                            }
                            else if (url_scheme->is_string("default_value")) {
                                args_.push_back(url_scheme->get("default_value").s());
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

                controller_ = controller_str;
            }
        }

        std::string Router::get_hostname() {
            return framework_->request_->base()[boost::beast::http::field::host].to_string();
        }

        std::string Router::get_lang() {
            return lang_;
        }

        std::string Router::get_controller() {
            return controller_;
        }

        std::vector<std::string> Router::get_args() {
            return args_;
        }

        std::string Router::get_post() const {
            return framework_->request_->body();
        }

        std::map<std::string, std::string> Router::get_cookies() {
            if (!cookies_initialized_) {
                std::string cookies_string = framework_->request_->base()[boost::beast::http::field::cookie].to_string();

                std::string key = "";
                std::string value = "";
                bool grabbing_value_part = false;

                for (unsigned int i = 0; i < cookies_string.length(); ++i) {
                    char val = cookies_string[i];

                    if (val == ';') {
                        cookies_.emplace(std::make_pair(key, value));
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
                    cookies_.emplace(std::make_pair(key, value));
                }
            }

            return cookies_;
        }

        std::string Router::get_cookie(const std::string& cookie_name, bool* cookie_exists) {
            auto cookies = get_cookies();

            auto it = cookies.find(cookie_name);
            if (it != cookies.end()) {
                if (cookie_exists != nullptr) {
                    *cookie_exists = true;
                }

                return it->second;
            }

            if (cookie_exists != nullptr) {
                *cookie_exists = false;
            }

            return "";
        }
    }  // namespace Core
}  // namespace Vortex
