#include <VortexFramework/Script/DeltaScriptEngine.h>
#ifdef HAS_FEATURE_DELTASCRIPT
#include <DeltaScript/DeltaScript.h>
#endif
#include <Core/CommonRuntime.h>

using namespace Vortex::Core;

namespace Vortex::VortexFramework::Script {

    DeltaScriptEngine::DeltaScriptEngine() {
#ifdef HAS_FEATURE_DELTASCRIPT
        _ctx = new DeltaScript::Context();
#endif
    }

    DeltaScriptEngine::~DeltaScriptEngine() {
#ifdef HAS_FEATURE_DELTASCRIPT
        if (_ctx != nullptr) {
            delete _ctx;
        }
#endif
    }

    void DeltaScriptEngine::init(FrameworkInterface* framework) {
        _framework = framework;

#ifdef HAS_FEATURE_DELTASCRIPT
        _ctx->add_native_function("function view.echo(value)", [](DeltaScript::Variable* var, void* data) {
            ((Framework*)(data))->view()->echo(var->find_child("value")->var->get_string());
            }, _framework);
        _ctx->add_native_function("function view.set_content_type(value)", [](DeltaScript::Variable* var, void* data) {
            ((Framework*)(data))->view()->set_content_type(var->find_child("value")->var->get_string());
            }, _framework);
        _ctx->add_native_function("function view.set_status_code(value)", [](DeltaScript::Variable* var, void* data) {
            ((Framework*)(data))->view()->set_status_code(var->find_child("value")->var->get_int());
            }, _framework);
        _ctx->add_native_function("function view.set_cookie(value)", [](DeltaScript::Variable* var, void* data) {
            ((Framework*)(data))->view()->set_cookie(var->find_child("value")->var->get_string());
            }, _framework);
        _ctx->add_native_function("function view.set_template(value)", [](DeltaScript::Variable* var, void* data) {
            ((Framework*)(data))->view()->set_template(var->find_child("value")->var->get_string());
            }, _framework);
        _ctx->add_native_function("function view.set_page(value)", [](DeltaScript::Variable* var, void* data) {
            ((Framework*)(data))->view()->set_page(var->find_child("value")->var->get_string());
            }, _framework);
        _ctx->add_native_function("function view.parse_page()", [](DeltaScript::Variable* var, void* data) {
            var->find_child("return")->var->set_string(
                ((Framework*)(data))->view()->parse_page()
            );
            }, _framework);
        _ctx->add_native_function("function view.finish()", [](DeltaScript::Variable* var, void* data) {
            ((Framework*)(data))->view()->finish();
            }, _framework);

        _ctx->add_native_function("function router.get_hostname()", [](DeltaScript::Variable* var, void* data) {
            var->find_child("return")->var->set_string(
                ((Framework*)(data))->router()->hostname()
            );
            }, _framework);
        _ctx->add_native_function("function router.get_lang()", [](DeltaScript::Variable* var, void* data) {
            var->find_child("return")->var->set_string(
                ((Framework*)(data))->router()->lang()
            );
            }, _framework);
        _ctx->add_native_function("function router.get_controller()", [](DeltaScript::Variable* var, void* data) {
            var->find_child("return")->var->set_string(
                ((Framework*)(data))->router()->controller()
            );
            }, _framework);
        _ctx->add_native_function("function router.get_args()", [](DeltaScript::Variable* var, void* data) {
            var->find_child("return")->var->set_as_array();
            std::vector<std::string> args = ((Framework*)(data))->router()->args();

            for (int i = 0; i < args.size(); ++i) {
                var->find_child("return")->var->set_array_val_at_index(i, new DeltaScript::Variable(args[i]));
            }

            }, _framework);
        _ctx->add_native_function("function router.get_post()", [](DeltaScript::Variable* var, void* data) {
            var->find_child("return")->var->set_string(
                ((Framework*)(data))->router()->request_post_body()
            );
            }, _framework);
        _ctx->add_native_function("function router.get_cookie(cookie_name)", [](DeltaScript::Variable* var, void* data) {
            var->find_child("return")->var->set_string(
                ((Framework*)(data))->router()->cookie(var->find_child("cookie_name")->var->get_string())
            );
            }, _framework);
        _ctx->add_native_function("function router.get_cookies_json()", [](DeltaScript::Variable* var, void* data) {
            auto cookies = ((Framework*)(data))->router()->cookies();
            Maze::Element cookies_obj(Maze::Type::Object);

            for (const auto& cookie : cookies) {
                cookies_obj.set(cookie.first, cookie.second);
            }

            var->find_child("return")->var->set_string(
                cookies_obj.to_json()
            );
            }, _framework);

        _ctx->add_native_function("function application.get_title()", [](DeltaScript::Variable* var, void* data) {
            var->find_child("return")->var->set_string(
                ((Framework*)(data))->application()->title()
            );
            }, _framework);
        _ctx->add_native_function("function application.get_id()", [](DeltaScript::Variable* var, void* data) {
            var->find_child("return")->var->set_string(
                ((Framework*)(data))->application()->id()
            );
            }, _framework);


        _ctx->add_native_function("function storage.simple_insert(database, collection, json_value)", [](DeltaScript::Variable* var, void* data) {
            Vortex::Core::CommonRuntime::instance().storage()->get_backend()
                ->simple_insert(
                    var->find_child("database")->var->get_string(),
                    var->find_child("collection")->var->get_string(),
                    var->find_child("json_value")->var->get_string()
                );
            }, nullptr);
        _ctx->add_native_function("function storage.simple_find_all(database, collection, json_simple_query)", [](DeltaScript::Variable* var, void* data) {
            var->find_child("return")->var->set_string(
                Vortex::Core::CommonRuntime::instance().storage()->get_backend()
                ->simple_find_all(
                    var->find_child("database")->var->get_string(),
                    var->find_child("collection")->var->get_string(),
                    var->find_child("json_simple_query")->var->get_string()
                )
            );
            }, nullptr);
        _ctx->add_native_function("function storage.simple_find_first(database, collection, json_simple_query)", [](DeltaScript::Variable* var, void* data) {
            var->find_child("return")->var->set_string(
                Vortex::Core::CommonRuntime::instance().storage()->get_backend()
                ->simple_find_first(
                    var->find_child("database")->var->get_string(),
                    var->find_child("collection")->var->get_string(),
                    var->find_child("json_simple_query")->var->get_string()
                )
            );
            }, nullptr);
        _ctx->add_native_function("function storage.simple_replace_first(database, collection, json_simple_query, replacement_json_value)", [](DeltaScript::Variable* var, void* data) {
            Vortex::Core::CommonRuntime::instance().storage()->get_backend()
                ->simple_replace_first(
                    var->find_child("database")->var->get_string(),
                    var->find_child("collection")->var->get_string(),
                    var->find_child("json_simple_query")->var->get_string(),
                    var->find_child("replacement_json_value")->var->get_string()
                );
            }, nullptr);
        _ctx->add_native_function("function storage.simple_delete_all(database, collection, json_simple_query)", [](DeltaScript::Variable* var, void* data) {
            Vortex::Core::CommonRuntime::instance().storage()->get_backend()
                ->simple_delete_all(
                    var->find_child("database")->var->get_string(),
                    var->find_child("collection")->var->get_string(),
                    var->find_child("json_simple_query")->var->get_string()
                );
            }, nullptr);
        _ctx->add_native_function("function storage.simple_delete_first(database, collection, json_simple_query)", [](DeltaScript::Variable* var, void* data) {
            Vortex::Core::CommonRuntime::instance().storage()->get_backend()
                ->simple_delete_first(
                    var->find_child("database")->var->get_string(),
                    var->find_child("collection")->var->get_string(),
                    var->find_child("json_simple_query")->var->get_string()
                );
            }, nullptr);

        _ctx->add_native_function("function storage.get_database_list()", [](DeltaScript::Variable* var, void* data) {
            var->find_child("return")->var->set_as_array();
            auto list = Vortex::Core::CommonRuntime::instance().storage()->get_backend()
                ->get_database_list();
            for (int i = 0; i < list.size(); ++i) {
                var->find_child("return")->var->set_array_val_at_index(i, new DeltaScript::Variable(list[i]));
            }

            }, nullptr);
        _ctx->add_native_function("function storage.get_collection_list(database)", [](DeltaScript::Variable* var, void* data) {
            var->find_child("return")->var->set_as_array();
            auto list = Vortex::Core::CommonRuntime::instance().storage()->get_backend()
                ->get_collection_list(var->find_child("database")->var->get_string());
            for (int i = 0; i < list.size(); ++i) {
                var->find_child("return")->var->set_array_val_at_index(i, new DeltaScript::Variable(list[i]));
            }

            }, nullptr);
#endif
    }

    void DeltaScriptEngine::exec(const std::string& script) {
#ifdef HAS_FEATURE_DELTASCRIPT
        if (script.length() > 0) {
            try {
                _ctx->execute(script);
            }
            catch (DeltaScript::DeltaScriptException& e) {
                _framework->view()->echo("<i>Script error (DeltaScript engine):</i><pre>" + e.message + "</pre>");
                _framework->view()->respond();
                _framework->exit();
            }
            catch (...) {
                _framework->view()->echo("<i>Script error (DeltaScript engine)</i>");
                _framework->view()->respond();
                _framework->exit();
            }
        }
#else
        _framework->view()->echo("DeltaScript script engine is unavailable.");
        _framework->view()->respond();
        _framework->exit();
#endif
    }

    ScriptEngineInterface* get_new_deltascript_engine() {
        return new DeltaScriptEngine();
    }

}
