#include <Core/Application.h>
#include <Core/CommonRuntime.h>
#include <Core/Framework.h>
#include <Maze/Element.hpp>

namespace Vortex {
	namespace Core {
		Application::Application(Framework* framework) : framework_(framework) {

		}

		void Application::find(std::string app_id) {
			std::string redis_key = "vortex.core.application.value." + app_id;
			if (framework_->redis_->exists(redis_key)) {
				application_ = Maze::Object::from_json(framework_->redis_->get(redis_key));
			}

			if (application_.is_empty()) {
				Maze::Object query;
				query.set("_id", Maze::Object("$oid", app_id));

				application_ = Maze::Array::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
					->find("vortex", "apps", query.to_json()))
					.get(0).get_object();
				/*application_ = framework_->mongo_
					.get_collection("apps")
					.find_by_id(app_id);*/

				if (!application_.is_empty()) {
					framework_->redis_->set(redis_key, application_.to_json(0));
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
