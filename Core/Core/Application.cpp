#include <Core/Application.h>
#include <Core/CommonRuntime.h>
#include <Core/Framework.h>

namespace Vortex::Core {

    Application::Application(Framework* framework)
        : _framework(framework) {}

    void Application::find(const std::string& app_id) {
        const std::string cache_key = "vortex.core.application.value." + app_id;
        if (CommonRuntime::instance().cache()->exists(cache_key)) {
            _application = Maze::Element::from_json(CommonRuntime::instance().cache()->get(cache_key));
        }

        if (!_application.has_children()) {
            Maze::Element query({ "_id" }, { Maze::Element({"$oid"}, {app_id}) });

            _application = Maze::Element::from_json(Core::CommonRuntime::instance().storage()->get_backend()
                ->simple_find_first("vortex", "apps", query.to_json()));

            if (_application.has_children()) {
                CommonRuntime::instance().cache()->set(cache_key, _application.to_json(0));
            }
        }

        if (!_application.has_children()) {
            _framework->view()->echo("Application associated with this hostname does not exist");
            _framework->exit();
        }
    }

    const std::string& Application::get_id() const {
        return _application.get("_id").get("$oid").s();
    }

    const std::string& Application::get_title() const {
        return _application.get("title").s();
    }

    const Maze::Element Application::get_config() const {
        if (_application.is_object("config")) {
            return _application.get("config");
        }

        return Maze::Element(Maze::Type::Object);
    }

    const std::string& Application::get_script() const {
        return _application.get("script").s();
    }

    const std::string& Application::get_post_script() const {
        return _application.get("post_script").s();
    }

    Maze::Element Application::find_object_in_application_storage(const std::string& collection, const Maze::Element& query, bool search_other_storages) const {
        std::string database;
        Maze::Element result;

        if (_framework->config()->get("application").is_string("database")) {
            database = _framework->config()->get("application").get("database").s();

            if (Core::CommonRuntime::instance().storage()->get_backend()->collection_exists(database, collection)) {
                result = Maze::Element::from_json(Core::CommonRuntime::instance().storage()->get_backend()
                    ->simple_find_first(database, collection, query.to_json()));

                if (result.has_children()) {
                    return result;
                }
            }
        }

        if (get_id().length() > 0) {
            database = get_id();

            if (Core::CommonRuntime::instance().storage()->get_backend()->collection_exists(database, collection)) {
                result = Maze::Element::from_json(Core::CommonRuntime::instance().storage()->get_backend()
                    ->simple_find_first(database, collection, query.to_json()));

                if (result.has_children()) {
                    return result;
                }
            }
        }

        if (search_other_storages) {
            database = "vortex";

            result = Maze::Element::from_json(Core::CommonRuntime::instance().storage()->get_backend()
                ->simple_find_first(database, collection, query.to_json()));
        }

        return result;
    }

}
