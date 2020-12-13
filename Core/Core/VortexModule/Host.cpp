#include <Core/VortexModule/Host.h>
#include <Core/CommonRuntime.h>

namespace Vortex::Core::VortexModule {

	Host::Host(FrameworkInterface* framework)
		: HostInterface(framework) {}

	void Host::init(const std::string& hostname) {
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
			_framework->view()->echo("Nothing is running on this hostname");
			_framework->exit();
		}
	}

	std::string Host::id() {
		return _host.get("_id").get("$oid").get_string();
	}

	std::string Host::hostname() {
		return _host.get("hostname").get_string();
	}

	std::string Host::application_id() {
		return _host.get("app_id").get_string();
	}

	Maze::Element Host::config() {
		if (_host.is_object("config")) {
			return _host.get("config");
		}

		return Maze::Element(Maze::Type::Object);
	}

	std::string Host::script() {
		return _host.get("script").get_string();
	}

	std::string Host::post_script() {
		return _host.get("post_script").get_string();
	}

}
