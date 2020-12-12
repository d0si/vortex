#include <Core/Controller.h>
#include <Core/CommonRuntime.h>
#include <Core/Framework.h>

namespace Vortex::Core {

    Controller::Controller(Framework* framework)
        : _framework(framework) {}

    void Controller::find(std::string app_id, std::string name, std::string method) {
        std::string cache_key = "vortex.core.controller.value." + app_id + "." + name + "." + method;
        if (CommonRuntime::instance().cache()->exists(cache_key)) {
            _controller = Maze::Element::from_json(CommonRuntime::instance().cache()->get(cache_key));
        }

        if (!_controller.has_children()) {
            Maze::Element query(
                { "$or", "name", "method" },
                    {
                        Maze::Element({
                            Maze::Element({"app_id"}, {app_id}),
                            Maze::Element({"app_id"}, {Maze::Element::get_null_element()}),
                        }),
                        name,
                        method
                    });

            _controller = _framework->application()->find_object_in_application_storage("controllers", query);

            if (_controller.has_children()) {
                CommonRuntime::instance().cache()->set(cache_key, _controller.to_json(0));
            }
        }

        if (!_controller.has_children()) {
            _framework->view()->echo("Controller " + name + " not found.");
            _framework->exit();
        }
    }

    const std::string& Controller::get_id() const {
        return _controller.get("_id").get("$oid").s();
    }

    const std::string& Controller::get_name() const {
        return _controller.get("name").s();
    }

    const Maze::Element Controller::get_app_ids() const {
        if (_controller.is_array("app_ids")) {
            return _controller.get("app_ids");
        }

        return Maze::Element(Maze::Type::Array);
    }

    const std::string& Controller::get_script() const {
        return _controller.get("script").s();
    }

    const std::string& Controller::get_post_script() const {
        return _controller.get("post_script").s();
    }

    const std::string& Controller::get_content_type() const {
        return _controller.get("content_type").s();
    }

    const std::string& Controller::get_method() const {
        return _controller.get("method").s();
    }

}
