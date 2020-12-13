#include <Core/VortexModule/View.h>
#include <Core/CommonRuntime.h>

namespace Vortex::Core::VortexModule {

    View::View(FrameworkInterface* framework)
        : ViewInterface(framework) {}

    void View::output() {
        _rendered += parse_template();

        respond();
    }

    void View::respond() {
        _framework->response()->body() = _rendered;
    }

    void View::echo(const std::string& contents) {
        _rendered += contents;
    }

    void View::set_content_type(const std::string& content_type) {
        _framework->response()->set(boost::beast::http::field::content_type, content_type);
    }

    void View::set_status_code(int status_code) {
        _framework->response()->result(boost::beast::http::int_to_status(status_code));
    }

    void View::set_cookie(const std::string& cookie_name, const std::string& value, const std::string& params) {
        set_cookie(cookie_name + '=' + value + ";" + (params.length() > 0 ? params + ";" : ""));
    }

    void View::set_cookie(const std::string& cookie_string) {
        _framework->response()->insert(boost::beast::http::field::set_cookie, cookie_string);
    }

    void View::clear() {
        _framework->response()->body() = "";
        _rendered.clear();
    }

    void View::finish() {
        _template.remove_all_children();
        _page.remove_all_children();
        respond();
    }

    std::string View::parse(const std::string& code) {
        const std::string old_rendered = _rendered;
        _rendered.clear();

        enum class grabbing_stage {
            String, Script, Echo, Comment
        };

        std::string script_code;
        grabbing_stage stage = grabbing_stage::String;

        for (size_t i = 0; i < code.length(); ++i) {
            char current = code[i];

            if (stage == grabbing_stage::String) {
                if (current == '{') {
                    char next = code[i + 1];

                    if (next == '{') {
                        stage = grabbing_stage::Script;
                        script_code.clear();
                        ++i;
                    }
                    else if (next == '=') {
                        stage = grabbing_stage::Echo;
                        script_code.clear();
                        ++i;
                    }
                    else if (next == '#') {
                        stage = grabbing_stage::Comment;
                        script_code.clear();
                        ++i;
                    }
                    else if (next == '\\') {
                        _rendered += current;
                        i++;
                    }
                    else {
                        _rendered += current;
                    }
                }
                else {
                    _rendered += current;
                }
            }
            else if (stage == grabbing_stage::Script) {
                if (current == '}') {
                    char next = code[i + 1];

                    if (next == '}') {
                        _framework->script()->exec(script_code);

                        script_code.clear();

                        stage = grabbing_stage::String;
                        ++i;

                        /*if (code[i + 2] == '\n') {
                            ++i;
                        }*/
                    }
                    else if (next == '\\') {
                        script_code += current;
                        ++i;
                    }
                    else {
                        script_code += current;
                    }
                }
                else {
                    script_code += current;
                }
            }
            else if (stage == grabbing_stage::Echo) {
                if (current == '=') {
                    char next = code[i + 1];

                    if (next == '}') {
                        _framework->script()->exec("var results = (" + script_code + "); if (results != undefined) { view.echo(results); }");

                        script_code.clear();

                        stage = grabbing_stage::String;
                        ++i;

                        /*if (code[i + 2] == '\n') {
                            ++i;
                        }*/
                    }
                    else if (next == '\\') {
                        script_code += current;
                        ++i;
                    }
                    else {
                        script_code += current;
                    }
                }
                else {
                    script_code += current;
                }
            }
            else if (stage == grabbing_stage::Comment) {
                if (current == '#') {
                    char next = code[i + 1];

                    if (next == '}') {
                        stage = grabbing_stage::String;
                        ++i;

                        /*if (code[i + 2] == '\n') {
                            ++i;
                        }*/
                    }
                    else if (next == '\\') {
                        ++i;
                    }
                }
            }
        }

        std::string new_rendered = _rendered;
        _rendered = old_rendered;
        return new_rendered;
    }

    void View::set_template(const std::string& name) {
        _template.remove_all_children();

        std::string cache_key = "vortex.core.template.value." + _framework->application()->id() + "." + name;
        if (CommonRuntime::instance().cache()->exists(cache_key)) {
            _template = Maze::Element::from_json(CommonRuntime::instance().cache()->get(cache_key));
        }

        if (!_template.has_children()) {
            Maze::Element query(
                { "name", "app_id" },
                { name, _framework->application()->id() }
            );

            _template = _framework->application()->find_object_in_application_storage("templates", query);

            if (!_template.has_children()) {
                query["app_id"].set_as_null();

                _template = _framework->application()->find_object_in_application_storage("templates", query);
            }

            if (_template.has_children()) {
                CommonRuntime::instance().cache()->set(cache_key, _template.to_json(0));
            }
        }

        if (!_template.has_children()) {
            _framework->view()->echo("Template " + name + " not found");
            _framework->exit();
        }
    }

    std::string View::parse_template() {
        if (_template.is_string("contents")) {
            return parse(_template["contents"].get_string());
        }

        return "";
    }

    void View::set_page(const std::string& name) {
        _page.remove_all_children();

        std::string cache_key = "vortex.core.page.value." + _framework->application()->id() + "." + name;
        if (CommonRuntime::instance().cache()->exists(cache_key)) {
            _page = Maze::Element::from_json(CommonRuntime::instance().cache()->get(cache_key));
        }

        if (!_page.has_children()) {
            Maze::Element query(
                { "name", "app_id" },
                { name, _framework->application()->id() }
            );

            _page = _framework->application()->find_object_in_application_storage("pages", query);

            if (!_page.has_children()) {
                query["app_id"].set_as_null();

                _page = _framework->application()->find_object_in_application_storage("pages", query);
            }

            if (_page.has_children()) {
                CommonRuntime::instance().cache()->set(cache_key, _page.to_json(0));
            }
        }

        if (!_page.has_children()) {
            _page.set("contents", "Page " + name + " not found");
        }
    }

    std::string View::parse_page() {
        if (_page.is_string("contents")) {
            return parse(_page["contents"].get_string());
        }

        return "";
    }

}
