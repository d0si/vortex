#include <Core/Application.h>
#include <Core/CommonRuntime.h>
#include <Core/Framework.h>
#include <Maze/Element.hpp>

namespace Vortex {
	namespace Core {
		Application::Application(Framework* framework) : framework_(framework) {

		}

		void Application::find(std::string app_id) {
			const std::string cache_key = "vortex.core.application.value." + app_id;
			if (CommonRuntime::Instance.get_cache()->exists(cache_key)) {
				application_ = Maze::Object::from_json(CommonRuntime::Instance.get_cache()->get(cache_key));
			}

			if (application_.is_empty()) {
				Maze::Object query;
				query.set("_id", Maze::Object("$oid", app_id));

				application_ = Maze::Object::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
					->simple_find_first("vortex", "apps", query.to_json()));

				if (!application_.is_empty()) {
					CommonRuntime::Instance.get_cache()->set(cache_key, application_.to_json(0));
				}
			}

			if (application_.is_empty()) {
				framework_->view_.echo("Application associated with this hostname does not exist");
				framework_->exit();
			}
		}

		std::string Application::get_id() {
			return application_["_id"].get_object()["$oid"].get_string();
		}

		std::string Application::get_title() {
			return application_["title"].get_string();
		}

		Maze::Object Application::get_config() {
			return application_["config"].get_object();
		}

		std::string Application::get_script() {
			return application_["script"].get_string();
		}

		std::string Application::get_post_script() {
			return application_["post_script"].get_string();
		}
	}  // namespace Core
}  // namespace Vortex
