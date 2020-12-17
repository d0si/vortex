#include <VortexBase/Application.h>
#include <Core/GlobalRuntime.h>

using Vortex::Core::RuntimeInterface;
using Vortex::Core::GlobalRuntime;

namespace VortexBase {

    Application::Application(RuntimeInterface* runtime)
        : ApplicationInterface(runtime) {}

    void Application::init(const std::string& application_id) {
        const std::string cache_key = "vortex.core.application.value." + application_id;
        if (GlobalRuntime::instance().cache().exists(cache_key)) {
            _application = Maze::Element::from_json(GlobalRuntime::instance().cache().get(cache_key));
        }

        if (!_application.has_children()) {
            Maze::Element query({ "_id" }, { Maze::Element({"$oid"}, {application_id}) });

            _application = Maze::Element::from_json(GlobalRuntime::instance().storage().get_backend()
                ->simple_find_first("vortex", "apps", query.to_json()));

            if (_application.has_children()) {
                GlobalRuntime::instance().cache().set(cache_key, _application.to_json(0));
            }
        }

        if (!_application.has_children()) {
            _runtime->view()->echo("Application associated with this hostname does not exist");
            _runtime->exit();
        }
    }

    std::string Application::id() {
        return _application.get("_id").get("$oid").get_string();
    }

    std::string Application::title() {
        return _application.get("title").get_string();
    }

    Maze::Element Application::config() {
        if (_application.is_object("config")) {
            return _application.get("config");
        }

        return Maze::Element(Maze::Type::Object);
    }

    std::string Application::script() {
        return _application.get("script").get_string();
    }

    std::string Application::post_script() {
        return _application.get("post_script").get_string();
    }

    Maze::Element Application::find_object_in_application_storage(const std::string& collection, const Maze::Element& query, bool search_other_storages) {
        std::string database;
        Maze::Element result;

        if (_runtime->config()->get("application").is_string("database")) {
            database = _runtime->config()->get("application").get("database").s();

            if (GlobalRuntime::instance().storage().get_backend()->collection_exists(database, collection)) {
                result = Maze::Element::from_json(GlobalRuntime::instance().storage().get_backend()
                    ->simple_find_first(database, collection, query.to_json()));

                if (result.has_children()) {
                    return result;
                }
            }
        }

        if (id().length() > 0) {
            database = id();

            if (GlobalRuntime::instance().storage().get_backend()->collection_exists(database, collection)) {
                result = Maze::Element::from_json(GlobalRuntime::instance().storage().get_backend()
                    ->simple_find_first(database, collection, query.to_json()));

                if (result.has_children()) {
                    return result;
                }
            }
        }

        if (search_other_storages) {
            database = "vortex";

            result = Maze::Element::from_json(GlobalRuntime::instance().storage().get_backend()
                ->simple_find_first(database, collection, query.to_json()));
        }

        return result;
    }

}
