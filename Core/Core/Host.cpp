#include <Core/Router.h>
#include <Core/CommonRuntime.h>
#include <Core/Framework.h>
#include <Maze/Element.hpp>

namespace Vortex {
	namespace Core {
		Host::Host(Framework* framework) : framework_(framework) {

		}

		void Host::find(std::string hostname) {
			std::string cache_key = "vortex.core.host.value." + hostname;
			if (CommonRuntime::Instance.get_cache()->exists(cache_key)) {
				host_ = Maze::Object::from_json(CommonRuntime::Instance.get_cache()->get(cache_key));
			}

			if (host_.is_empty()) {
				host_ = Maze::Object::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
					->simple_find_first("vortex", "hosts", Maze::Object("hostname", hostname).to_json()));

				if (!host_.is_empty()) {
					CommonRuntime::Instance.get_cache()->set(cache_key, host_.to_json(0));
				}
			}

			if (host_.is_empty()) {
				framework_->view_.echo("Nothing is running on this hostname");
				framework_->exit();
			}
		}

		std::string Host::get_id() {
			return host_["_id"].get_object()["$oid"].get_string();
		}

		std::string Host::get_hostname() {
			return host_["hostname"].get_string();
		}

		std::string Host::get_app_id() {
			return host_["app_id"].get_string();
		}

		Maze::Object Host::get_config() {
			return host_["config"].get_object();
		}

		std::string Host::get_script() {
			return host_["script"].get_string();
		}

		std::string Host::get_post_script() {
			return host_["post_script"].get_string();
		}
	}  // namespace Core
}  // namespace Vortex
