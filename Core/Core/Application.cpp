#include <Core/Application.h>
#include <Core/CommonRuntime.h>
#include <Core/Framework.h>

namespace Vortex {
	namespace Core {
		Application::Application(Framework* framework) : framework_(framework) {

		}

		void Application::find(const std::string& app_id) {
			const std::string cache_key = "vortex.core.application.value." + app_id;
			if (CommonRuntime::Instance.get_cache()->exists(cache_key)) {
				application_ = Maze::Element::from_json(CommonRuntime::Instance.get_cache()->get(cache_key));
			}

			if (!application_.has_children()) {
				Maze::Element query({ "_id" }, { Maze::Element({"$oid"}, {app_id}) });

				application_ = Maze::Element::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
					->simple_find_first("vortex", "apps", query.to_json()));

				if (application_.has_children()) {
					CommonRuntime::Instance.get_cache()->set(cache_key, application_.to_json(0));
				}
			}

			if (!application_.has_children()) {
				framework_->view_.echo("Application associated with this hostname does not exist");
				framework_->exit();
			}
		}

		const std::string& Application::get_id() const {
			return application_.get("_id").get("$oid").s();
		}

		const std::string& Application::get_title() const {
			return application_.get("title").s();
		}

		const Maze::Element Application::get_config() const {
			if (application_.is_object("config")) {
				return application_.get("config");
			}

			return Maze::Element(Maze::Type::Object);
		}

		const std::string& Application::get_script() const {
			return application_.get("script").s();
		}

		const std::string& Application::get_post_script() const {
			return application_.get("post_script").s();
		}

		Maze::Element Application::find_object_in_application_storage(const std::string& collection, const Maze::Element& query, bool search_other_storages) const {
			std::string database;
			Maze::Element result;

			if (framework_->get_config().get("application").is_string("database")) {
				database = framework_->get_config().get("application").get("database").s();

				if (Core::CommonRuntime::Instance.get_storage()->get_backend()->collection_exists(database, collection)) {
					result = Maze::Element::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
						->simple_find_first(database, collection, query.to_json()));

					if (result.has_children()) {
						return result;
					}
				}
			}

			if (get_id().length() > 0) {
				database = get_id();

				if (Core::CommonRuntime::Instance.get_storage()->get_backend()->collection_exists(database, collection)) {
					result = Maze::Element::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
						->simple_find_first(database, collection, query.to_json()));

					if (result.has_children()) {
						return result;
					}
				}
			}

			if (search_other_storages) {
				database = "vortex";

				result = Maze::Element::from_json(Core::CommonRuntime::Instance.get_storage()->get_backend()
					->simple_find_first(database, collection, query.to_json()));
			}

			return result;
		}
	}  // namespace Core
}  // namespace Vortex
