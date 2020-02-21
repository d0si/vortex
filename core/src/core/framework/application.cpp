#include <core/framework/application.h>
#include <core/framework/framework.h>
#include <maze/element.h>

namespace vortex {
	namespace core {
		namespace framework {
			Application::Application(Framework* framework) : framework_(framework) {

			}

			void Application::find(std::string app_id) {
				std::string redis_key = "vortex.core.application.value." + app_id;
				if (framework_->redis_->exists(redis_key)) {
					application_ = maze::object::from_json(framework_->redis_->get(redis_key));
				}

				if (application_.is_empty()) {
					application_ = framework_->mongo_
						.get_collection("apps")
						.find_by_id(app_id);

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

			maze::object Application::get_config() {
				return application_["config"].get_object();
			}

			std::string Application::get_script() {
				return application_["script"].get_string();
			}

			std::string Application::get_post_script() {
				return application_["post_script"].get_string();
			}
		}  // namespace framework
	}  // namespace core
}  // namespace vortex
