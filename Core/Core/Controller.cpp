#include <Core/Controller.h>
#include <Core/CommonRuntime.h>
#include <Core/Framework.h>

namespace Vortex {
    namespace Core {
        Controller::Controller(Framework* framework) : framework_(framework) {

        }

        void Controller::find(std::string app_id, std::string name, std::string method) {
            std::string cache_key = "vortex.core.controller.value." + app_id + "." + name + "." + method;
            if (CommonRuntime::Instance.get_cache()->exists(cache_key)) {
                controller_ = Maze::Element::from_json(CommonRuntime::Instance.get_cache()->get(cache_key));
            }

            if (!controller_.has_children()) {
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

                controller_ = framework_->application_.find_object_in_application_storage("controllers", query);

                if (controller_.has_children()) {
                    CommonRuntime::Instance.get_cache()->set(cache_key, controller_.to_json(0));
                }
            }

            if (!controller_.has_children()) {
                framework_->view_.echo("Controller " + name + " not found.");
                framework_->exit();
            }
        }

        const std::string& Controller::get_id() const {
            return controller_.get("_id").get("$oid").s();
        }

        const std::string& Controller::get_name() const {
            return controller_.get("name").s();
        }

        const Maze::Element Controller::get_app_ids() const {
            if (controller_.is_array("app_ids")) {
                return controller_.get("app_ids");
            }

            return Maze::Element(Maze::Type::Array);
        }

        const std::string& Controller::get_script() const {
            return controller_.get("script").s();
        }

        const std::string& Controller::get_post_script() const {
            return controller_.get("post_script").s();
        }

        const std::string& Controller::get_content_type() const {
            return controller_.get("content_type").s();
        }

        const std::string& Controller::get_method() const {
            return controller_.get("method").s();
        }
    }  // namespace Core
}  // namespace Vortex
