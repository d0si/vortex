#include <Core/Router.h>
#include <Core/Framework.h>
#include <Maze/Object.hpp>
#include <Maze/Element.hpp>

namespace Vortex {
	namespace Core {
		Router::Router(Framework* framework) : framework_(framework) {
			lang_ = "en";
			controller_ = "index";

			std::string target = framework_->request_->target().to_string();
			request_uri_ = target.substr(1, target.length() - 1);
		}

		void Router::setup() {
			Maze::Object router_config = framework_->config_["router"].get_object();

			if (router_config.is_object("routes")) {
				Maze::Object routes = router_config["routes"].get_object();

				for (auto route = routes.begin(); route != routes.end(); route++) {
					std::string route_url = route->first;

					if (route->second.is_object() &&
						request_uri_.substr(0, route_url.length()) == route_url) {
						Maze::Object route_obj = route->second;

						if (route_obj.is_string("default_lang")) {
							lang_ = route_obj["default_lang"].get_string();
						}
						if (route_obj.is_string("default_controller")) {
							controller_ = route_obj["default_controller"].get_string();
						}
						if (route_obj.is_array("url_schemes")) {
							router_config.set("url_schemes", route_obj["url_schemes"].get_array());
						}
					}
				}
			}

			if (!router_config.is_array("url_schemes")) {
				router_config.set("url_schemes", Maze::Array()
					<< "lang"
					<< Maze::Object("type", "controller").set("default_value", "index")
					<< "controller"
					<< "args");
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
			Maze::Array url_schemes = router_config["url_schemes"].get_array();
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
					Maze::Object scheme = url_scheme->get_object();

					if (scheme.is_string("type")) {
						std::string type = scheme["type"].get_string();

						if (type == "lang") {
							if (scheme.is_string("value")) {
								lang_ = scheme["value"].get_string();
							}
							else if (i < parts_count) {
								std::string lang;

								if (scheme.is_string("prefix")) {
									lang += scheme["prefix"].get_string();
								}

								lang += request_uri_parts[i];

								if (scheme.is_string("suffix")) {
									lang += scheme["suffix"].get_string();
								}

								lang_ = lang;
							}
							else if (scheme.is_string("default_value")) {
								lang_ = scheme["default_value"].get_string();
							}
						}
						else if (type == "controller") {
							if (scheme.is_string("value")) {
								controller_parts.push_back(scheme["value"].get_string());
							}
							else if (i < parts_count) {
								std::string controller;

								if (scheme.is_string("prefix")) {
									controller += scheme["prefix"].get_string();
								}

								controller += request_uri_parts[i];

								if (scheme.is_string("suffix")) {
									controller += scheme["suffix"].get_string();
								}

								controller_parts.push_back(controller);
							}
							else if (scheme.is_string("default_value")) {
								controller_parts.push_back(scheme["default_value"].get_string());
							}
						}
						else if (type == "args") {
							if (i < parts_count) {
								if (scheme.is_int("count")) {
									int arg_count = scheme["count"].get_int();

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
							if (scheme.is_string("value")) {
								args_.push_back(scheme["value"].get_string());
							}
							else if (i < parts_count) {
								std::string arg;

								if (scheme.is_string("prefix")) {
									arg += scheme["prefix"].get_string();
								}

								arg += request_uri_parts[i];

								if (scheme.is_string("suffix")) {
									arg += scheme["suffix"].get_string();
								}

								args_.push_back(arg);
							}
							else if (scheme.is_string("default_value")) {
								args_.push_back(scheme["default_value"]);
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