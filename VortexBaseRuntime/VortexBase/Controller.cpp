#include <VortexBase/Controller.h>
#include <Core/GlobalRuntime.h>
#include <Core/Modules/DependencyInjection.h>

using Vortex::Core::RuntimeInterface;
using Vortex::Core::GlobalRuntime;

namespace VortexBase {

    Controller::Controller(RuntimeInterface* runtime)
        : ControllerInterface(runtime) {}

    void Controller::init(const std::string& application_id, const std::string& name, const std::string& method) {
        if (_runtime->di()->plugin_manager()->on_controller_init_before(_runtime))
            return;

        std::string cache_key = "vortex.core.controller.value." + application_id + "." + name + "." + method;
        if (GlobalRuntime::instance().cache().exists(cache_key)) {
            _controller = Maze::Element::from_json(GlobalRuntime::instance().cache().get(cache_key));
        }

        if (!_controller.has_children()) {
            Maze::Element or_query(Maze::Type::Array);
            or_query << Maze::Element({ "app_id" }, { Maze::Element(application_id) })
                << Maze::Element({ "app_id" }, {Maze::Element::get_null_element()});

            Maze::Element query(Maze::Type::Object);
            query.set("$or", or_query);
            query.set("name", name);
            query.set("method", method);

            _controller = _runtime->application()->find_object_in_application_storage("controllers", query);

            if (_controller.has_children()) {
                GlobalRuntime::instance().cache().set(cache_key, _controller.to_json(0));
            }
        }

        if (_runtime->di()->plugin_manager()->on_controller_init_after(_runtime))
            return;

        if (!_controller.has_children()) {
            _runtime->view()->echo("Controller " + name + " not found.");
            _runtime->exit();
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
