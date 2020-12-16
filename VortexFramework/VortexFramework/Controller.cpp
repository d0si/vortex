#include <VortexFramework/Controller.h>
#include <Core/GlobalRuntime.h>

using namespace Vortex::Core;

namespace Vortex::VortexFramework {

    Controller::Controller(FrameworkInterface* framework)
        : ControllerInterface(framework) {}

    void Controller::init(const std::string& application_id, const std::string& name, const std::string& method) {
        std::string cache_key = "vortex.core.controller.value." + application_id + "." + name + "." + method;
        if (GlobalRuntime::instance().cache()->exists(cache_key)) {
            _controller = Maze::Element::from_json(GlobalRuntime::instance().cache()->get(cache_key));
        }

        if (!_controller.has_children()) {
            Maze::Element or_query(Maze::Type::Array);
            or_query << Maze::Element({ "app_id" }, { Maze::Element(application_id) })
                << Maze::Element({ "app_id" }, {Maze::Element::get_null_element()});

            Maze::Element query(Maze::Type::Object);
            query.set("$or", or_query);
            query.set("name", name);
            query.set("method", method);

            _controller = _framework->application()->find_object_in_application_storage("controllers", query);

            if (_controller.has_children()) {
                GlobalRuntime::instance().cache()->set(cache_key, _controller.to_json(0));
            }
        }

        if (!_controller.has_children()) {
            _framework->view()->echo("Controller " + name + " not found.");
            _framework->exit();
        }
    }

    std::string Controller::id() {
        return _controller.get("_id").get("$oid").get_string();
    }

    std::string Controller::name() {
        return _controller.get("name").get_string();
    }

    Maze::Element Controller::app_ids() {
        if (_controller.is_array("app_ids")) {
            return _controller.get("app_ids");
        }

        return Maze::Element(Maze::Type::Array);
    }

    std::string Controller::script() {
        return _controller.get("script").get_string();
    }

    std::string Controller::post_script() {
        return _controller.get("post_script").get_string();
    }

    std::string Controller::content_type() {
        return _controller.get("content_type").get_string();
    }

    std::string Controller::method() {
        return _controller.get("method").get_string();
    }

}
