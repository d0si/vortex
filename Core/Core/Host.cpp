#include <Core/Router.h>
#include <Core/CommonRuntime.h>
#include <Core/Framework.h>

namespace Vortex {
	namespace Core {
		Host::Host(Framework* framework) : framework_(framework) {

		}

		void Host::find(const std::string& hostname) {
			std::string cache_key = "vortex.core.host.value." + hostname;
			if (CommonRuntime::Instance.get_cache()->exists(cache_key)) {
				host_ = Maze::Element::from_json(CommonRuntime::Instance.get_cache()->get(cache_key));
			}

			if (!host_.has_children()) {
				host_ = Maze::Element::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
					->simple_find_first("vortex", "hosts", Maze::Element({ "hostname" }, { hostname }).to_json()));

				if (host_.has_children()) {
					CommonRuntime::Instance.get_cache()->set(cache_key, host_.to_json(0));
				}
			}

			if (!host_.has_children()) {
				framework_->view_.echo("Nothing is running on this hostname");
				framework_->exit();
			}
		}

		const std::string& Host::get_id() const {
			return host_.get("_id").get("$oid").s();
		}

		const std::string& Host::get_hostname() const {
			return host_.get("hostname").s();
		}

		const std::string& Host::get_app_id() const {
			return host_.get("app_id").s();
		}

		const Maze::Element Host::get_config() const {
			if (host_.is_object("config")) {
				return host_.get("config");
			}

			return Maze::Element(Maze::Type::Object);
		}

		const std::string& Host::get_script() const {
			return host_.get("script").s();
		}

		const std::string& Host::get_post_script() const {
			return host_.get("post_script").s();
		}
	}  // namespace Core
}  // namespace Vortex
