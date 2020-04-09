#include <Core/Script/DeltaScriptEngine.h>
#ifdef VORTEX_HAS_FEATURE_DELTASCRIPT
#include <DeltaScript/DeltaScript.h>
#endif
#include <Core/Framework.h>
#include <Core/CommonRuntime.h>

namespace Vortex {
    namespace Core {
        namespace Script {
            DeltaScriptEngine::DeltaScriptEngine() {
#ifdef VORTEX_HAS_FEATURE_DELTASCRIPT
                ctx_ = new DeltaScript::Context();
#endif
            }

            DeltaScriptEngine::~DeltaScriptEngine() {
#ifdef VORTEX_HAS_FEATURE_DELTASCRIPT
                if (ctx_ != nullptr) {
                    delete ctx_;
                }
#endif
            }

            void DeltaScriptEngine::setup(Framework* framework) {
                framework_ = framework;

#ifdef VORTEX_HAS_FEATURE_DUKTAPE
                ctx_->add_native_function("function view.echo(value)", [](DeltaScript::Variable* var, void* data) {
                    ((Framework*)(data))->view_.echo(var->find_child("value")->var->get_string());
                    }, framework_);
                ctx_->add_native_function("function view.set_content_type(value)", [](DeltaScript::Variable* var, void* data) {
                    ((Framework*)(data))->view_.set_content_type(var->find_child("value")->var->get_string());
                    }, framework_);
                ctx_->add_native_function("function view.set_status_code(value)", [](DeltaScript::Variable* var, void* data) {
                    ((Framework*)(data))->view_.set_status_code(var->find_child("value")->var->get_int());
                    }, framework_);
                ctx_->add_native_function("function view.set_cookie(value)", [](DeltaScript::Variable* var, void* data) {
                    ((Framework*)(data))->view_.set_cookie(var->find_child("value")->var->get_string());
                    }, framework_);
                ctx_->add_native_function("function view.set_template(value)", [](DeltaScript::Variable* var, void* data) {
                    ((Framework*)(data))->view_.set_template(var->find_child("value")->var->get_string());
                    }, framework_);
                ctx_->add_native_function("function view.set_page(value)", [](DeltaScript::Variable* var, void* data) {
                    ((Framework*)(data))->view_.set_page(var->find_child("value")->var->get_string());
                    }, framework_);
                ctx_->add_native_function("function view.parse_page()", [](DeltaScript::Variable* var, void* data) {
                    var->find_child("return")->var->set_string(
                        ((Framework*)(data))->view_.parse_page()
                    );
                    }, framework_);
                ctx_->add_native_function("function view.finish()", [](DeltaScript::Variable* var, void* data) {
                    ((Framework*)(data))->view_.finish();
                    }, framework_);

                ctx_->add_native_function("function router.get_hostname()", [](DeltaScript::Variable* var, void* data) {
                    var->find_child("return")->var->set_string(
                        ((Framework*)(data))->router_.get_hostname()
                    );
                    }, framework_);
                ctx_->add_native_function("function router.get_lang()", [](DeltaScript::Variable* var, void* data) {
                    var->find_child("return")->var->set_string(
                        ((Framework*)(data))->router_.get_lang()
                    );
                    }, framework_);
                ctx_->add_native_function("function router.get_controller()", [](DeltaScript::Variable* var, void* data) {
                    var->find_child("return")->var->set_string(
                        ((Framework*)(data))->router_.get_controller()
                    );
                    }, framework_);
                ctx_->add_native_function("function router.get_args()", [](DeltaScript::Variable* var, void* data) {
                    DeltaScript::Variable* return_var = var->find_child("return")->var;
                    /*return_var->set_as_array();

                    std::vector<std::string> args = ((Framework*)(data))->router_.get_args();
                    for (int i = 0; i < args.size(); ++i) {
                        return_var->set_array_val_at_index(i, new DeltaScript::Variable(args[i]));
                    }*/
                    }, framework_);
                ctx_->add_native_function("function router.get_post()", [](DeltaScript::Variable* var, void* data) {
                    var->find_child("return")->var->set_string(
                        ((Framework*)(data))->router_.get_post()
                    );
                    }, framework_);
                ctx_->add_native_function("function router.get_cookie(cookie_name)", [](DeltaScript::Variable* var, void* data) {
                    var->find_child("return")->var->set_string(
                        ((Framework*)(data))->router_.get_cookie(var->find_child("cookie_name")->var->get_string())
                    );
                    }, framework_);
                ctx_->add_native_function("function router.get_cookies_json()", [](DeltaScript::Variable* var, void* data) {
                    auto cookies = ((Framework*)(data))->router_.get_cookies();
                    Maze::Object cookies_obj;

                    for (auto cookie : cookies) {
                        cookies_obj.set(cookie.first, cookie.second);
                    }

                    var->find_child("return")->var->set_string(
                        cookies_obj.to_json()
                    );
                    }, framework_);

                ctx_->add_native_function("function application.get_title()", [](DeltaScript::Variable* var, void* data) {
                    var->find_child("return")->var->set_string(
                        ((Framework*)(data))->application_.get_title()
                    );
                    }, framework_);
                ctx_->add_native_function("function application.get_id()", [](DeltaScript::Variable* var, void* data) {
                    var->find_child("return")->var->set_string(
                        ((Framework*)(data))->application_.get_id()
                    );
                    }, framework_);


                ctx_->add_native_function("function storage.simple_insert(database, collection, json_value)", [](DeltaScript::Variable* var, void* data) {
                    Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                        ->simple_insert(
                            var->find_child("database")->var->get_string(),
                            var->find_child("collection")->var->get_string(),
                            var->find_child("json_value")->var->get_string()
                        );
                    }, nullptr);
                ctx_->add_native_function("function storage.simple_find_all(database, collection, json_simple_query)", [](DeltaScript::Variable* var, void* data) {
                    var->find_child("return")->var->set_string(
                        Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                        ->simple_find_all(
                            var->find_child("database")->var->get_string(),
                            var->find_child("collection")->var->get_string(),
                            var->find_child("json_simple_query")->var->get_string()
                        )
                    );
                    }, nullptr);
                ctx_->add_native_function("function storage.simple_find_first(database, collection, json_simple_query)", [](DeltaScript::Variable* var, void* data) {
                    var->find_child("return")->var->set_string(
                        Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                        ->simple_find_first(
                            var->find_child("database")->var->get_string(),
                            var->find_child("collection")->var->get_string(),
                            var->find_child("json_simple_query")->var->get_string()
                        )
                    );
                    }, nullptr);
                ctx_->add_native_function("function storage.simple_replace_first(database, collection, json_simple_query, replacement_json_value)", [](DeltaScript::Variable* var, void* data) {
                    Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                        ->simple_replace_first(
                            var->find_child("database")->var->get_string(),
                            var->find_child("collection")->var->get_string(),
                            var->find_child("json_simple_query")->var->get_string(),
                            var->find_child("replacement_json_value")->var->get_string()
                        );
                    }, nullptr);
                ctx_->add_native_function("function storage.simple_delete_all(database, collection, json_simple_query)", [](DeltaScript::Variable* var, void* data) {
                    Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                        ->simple_delete_all(
                            var->find_child("database")->var->get_string(),
                            var->find_child("collection")->var->get_string(),
                            var->find_child("json_simple_query")->var->get_string()
                        );
                    }, nullptr);
                ctx_->add_native_function("function storage.simple_delete_first(database, collection, json_simple_query)", [](DeltaScript::Variable* var, void* data) {
                    Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                        ->simple_delete_first(
                            var->find_child("database")->var->get_string(),
                            var->find_child("collection")->var->get_string(),
                            var->find_child("json_simple_query")->var->get_string()
                        );
                    }, nullptr);
#endif
            }

            void DeltaScriptEngine::exec(const std::string& script) {
#ifdef VORTEX_HAS_FEATURE_DUKTAPE
                if (script.length() > 0) {
                    try {
                        ctx_->execute(script);
        }
                    catch (DeltaScript::DeltaScriptException & e) {
                        framework_->view_.echo("<i>Script error (DeltaScript engine):</i><pre>" + e.message + "</pre>");
                        framework_->view_.respond();
                        framework_->exit();
                    }
                    catch (...) {
                        framework_->view_.echo("<i>Script error (DeltaScript engine)</i>");
                        framework_->view_.respond();
                        framework_->exit();
                    }
    }
#else
                framework_->view_.echo("DeltaScript script engine is unavailable.");
                framework_->view_.respond();
                framework_->exit();
#endif
}

            IScriptEngine* get_new_deltascript_engine() {
                return new DeltaScriptEngine();
            }
        }  // namespace Script
    }  // namespace Core
}  // namespace Vortex
