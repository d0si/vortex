#include <Core/Router.h>
#include <Core/CommonRuntime.h>
#include <Core/Framework.h>

namespace Vortex::Core {

	Host::Host(Framework* framework)
		: _framework(framework) {}

	void Host::find(const std::string& hostname) {
		std::string cache_key = "vortex.core.host.value." + hostname;
		if (CommonRuntime::instance().cache()->exists(cache_key)) {
			_host = Maze::Element::from_json(CommonRuntime::instance().cache()->get(cache_key));
		}

		if (!_host.has_children()) {
			_host = Maze::Element::from_json(Core::CommonRuntime::instance().storage()->get_backend()
				->simple_find_first("vortex", "hosts", Maze::Element({ "hostname" }, { hostname }).to_json()));

			if (_host.has_children()) {
				CommonRuntime::instance().cache()->set(cache_key, _host.to_json(0));
			}
		}

		if (!_host.has_children()) {
			_framework->view_.echo("Nothing is running on this hostname");
			_framework->exit();
		}
	}

	const std::string& Host::get_id() const {
		return _host.get("_id").get("$oid").s();
	}

	const std::string& Host::get_hostname() const {
		return _host.get("hostname").s();
	}

	const std::string& Host::get_app_id() const {
		return _host.get("app_id").s();
	}

	const Maze::Element Host::get_config() const {
		if (_host.is_object("config")) {
			return _host.get("config");
		}

		return Maze::Element(Maze::Type::Object);
	}

	const std::string& Host::get_script() const {
		return _host.get("script").s();
	}

	const std::string& Host::get_post_script() const {
		return _host.get("post_script").s();
	}

}
