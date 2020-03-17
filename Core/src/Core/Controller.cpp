#include <Core/Controller.h>
#include <Core/CommonRuntime.h>
#include <Core/Framework.h>
#include <Maze/Element.hpp>

namespace Vortex {
	namespace Core {
		Controller::Controller(Framework* framework) : framework_(framework) {

		}

		void Controller::find(std::string app_id, std::string name, std::string method) {
			Maze::Object query;
			query.set("$or", Maze::Array()
				<< Maze::Object("app_id", app_id)
				<< Maze::Object("app_id", Maze::Element::get_null()));
			query.set("name", name);
			query.set("method", method);

			controller_ = Maze::Object::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
				->simple_find_first("vortex", "controllers", query.to_json()));

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

		Maze::Array Controller::get_app_ids() {
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
