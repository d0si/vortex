#include <core/framework/router.h>
#include <core/framework/framework.h>
#include <maze/object.h>

namespace vortex {
namespace core {
namespace framework {

router::router(framework* framework) : framework_(framework) {
  lang_ = "en";
  controller_ = "index";

  std::string target = framework_->request_->target().to_string();
  request_uri_ = target.substr(1, target.length() - 1);
}

void router::setup() {
  maze::object router_config = framework_->config_["router"].get_object();

  if (router_config.is_object("routes")) {
    maze::object routes = router_config["routes"].get_object();

    for (auto route = routes.begin(); route != routes.end(); route++) {
      std::string route_url = route->first;

      if (route->second.is_object() &&
          request_uri_.substr(0, route_url.length()) == route_url) {
        maze::object route_obj = route->second;

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
    router_config.set("url_schemes", maze::array()
      << "lang"
      << maze::object("type", "controller").set("default_value", "index")
      << "controller"
      << "args");
  }

  std::vector<std::string> request_uri_parts;
  std::string request_uri_part;
  for (auto it = request_uri_.begin(); it != request_uri_.end(); it++) {
    if (*it == '/') {
      request_uri_parts.push_back(request_uri_part);
      request_uri_part = "";
    } else if (*it == '?') {
      break;
    } else if (*it == '#') {
      break;
    } else {
      request_uri_part += *it;
    }
  }
  if (request_uri_part.length() > 0) {
    request_uri_parts.push_back(request_uri_part);
  }

}

std::string router::get_hostname() {
  return framework_->request_->base()[boost::beast::http::field::host].to_string();
}

std::string router::get_lang() {
  return lang_;
}

std::string router::get_controller() {
  return controller_;
}

std::vector<std::string> router::get_args() {
  return args_;
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
