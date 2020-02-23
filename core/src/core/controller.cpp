#include <core/controller.h>
#include <core/framework.h>
#include <maze/element.h>

namespace Vortex {
	namespace Core {
		Controller::Controller(Framework* framework) : framework_(framework) {

		}

		void Controller::find(std::string app_id, std::string name, std::string method) {
			maze::object query;
			query["$or"] = maze::object("$or", maze::array()
				<< maze::object("app_id", app_id)
				<< maze::object("app_id", maze::element::get_null()));
			query["name"] = name;
			query["method"] = method;

			controller_ = framework_->mongo_
				.get_collection("controllers")
				.find_one(query);


			if (controller_.is_empty()) {
				framework_->view_.echo("Controller " + name + " not found.");
				framework_->exit();
			}
		}

		std::string Controller::get_id() {
			return controller_["_id"].get_object()["$oid"].get_string();
		}

		std::string Controller::get_name() {
			return controller_["name"].get_string();
		}

		maze::array Controller::get_app_ids() {
			return controller_["app_ids"].get_array();
		}

		std::string Controller::get_script() {
			return controller_["script"].get_string();
		}

		std::string Controller::get_post_script() {
			return controller_["post_script"].get_string();
		}

		std::string Controller::get_content_type() {
			return controller_["content_type"].get_string();
		}

		std::string Controller::get_method() {
			return controller_["method"].get_string();
		}
	}  // namespace Core
}  // namespace Vortex
