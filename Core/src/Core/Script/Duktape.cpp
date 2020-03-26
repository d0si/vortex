#include <Core/Script/Duktape.h>
#ifdef VORTEX_HAS_FEATURE_DUKTAPE
#include <duktape-cpp/DuktapeCpp.h>
#endif
#include <Core/Framework.h>
#include <Core/CommonRuntime.h>

#ifdef VORTEX_HAS_FEATURE_DUKTAPE
namespace DuktapeBindings {
    class View {
    private:
        Vortex::Core::Framework* framework_;

    public:
        View() {}
        View(Vortex::Core::Framework* framework) : framework_(framework) {}

        void echo(std::string content) {
            framework_->view_.echo(content);
        }

        void set_content_type(std::string content_type) {
            framework_->view_.set_content_type(content_type);
        }

        void set_status_code(int status_code) {
            framework_->view_.set_status_code(status_code);
        }

        void set_template(std::string name) {
            framework_->view_.set_template(name);
        }

        void set_page(std::string name) {
            framework_->view_.set_page(name);
        }

        std::string parse_page() {
            return framework_->view_.parse_page();
        }

        void finish() {
            return framework_->view_.finish();
        }

        template<class Inspector>
        static void inspect(Inspector& i) {
            i.construct(&std::make_shared<View>);
            i.method("echo", &View::echo);
            i.method("set_content_type", &View::set_content_type);
            i.method("set_status_code", &View::set_status_code);
            i.method("set_template", &View::set_template);
            i.method("set_page", &View::set_page);
            i.method("parse_page", &View::parse_page);
            i.method("finish", &View::finish);
        }
    };

    class Router {
    private:
        Vortex::Core::Framework* framework_;

    public:
        Router() {}
        Router(Vortex::Core::Framework* framework) : framework_(framework) {}

        std::string get_hostname() {
            return framework_->router_.get_hostname();
        }

        std::string get_lang() {
            return framework_->router_.get_lang();
        }

        std::string get_controller() {
            return framework_->router_.get_controller();
        }

        std::vector<std::string> get_args() {
            return framework_->router_.get_args();
        }

        std::string get_post() {
            return framework_->router_.get_post();
        }

        template<class Inspector>
        static void inspect(Inspector& i) {
            i.construct(&std::make_shared<Router>);
            i.method("get_hostname", &Router::get_hostname);
            i.method("get_lang", &Router::get_lang);
            i.method("get_controller", &Router::get_controller);
            i.method("get_args", &Router::get_args);
            i.method("get_post", &Router::get_post);
        }
    };

    class Application {
    private:
        Vortex::Core::Framework* framework_;

    public:
        Application() {}
        Application(Vortex::Core::Framework* framework) : framework_(framework) {}

        std::string get_id() {
            return framework_->application_.get_id();
        }

        std::string get_title() {
            return framework_->application_.get_title();
        }

        template<class Inspector>
        static void inspect(Inspector& i) {
            i.construct(&std::make_shared<Application>);
            i.method("get_id", &Application::get_id);
            i.method("get_title", &Application::get_title);
        }
    };

    class Storage {
    public:
        Storage() {}

        void simple_insert(const std::string& database, const std::string& collection, const std::string& json_value) {
            Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                ->simple_insert(database, collection, json_value);
        }

        std::string simple_find_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
            return Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                ->simple_find_all(database, collection, json_simple_query);
        }

        std::string simple_find_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
            return Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                ->simple_find_first(database, collection, json_simple_query);
        }

        void simple_replace_first(const std::string& database, const std::string& collection, const std::string& json_simple_query, const std::string& replacement_json_value) {
            Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                ->simple_replace_first(database, collection, json_simple_query, replacement_json_value);
        }

        void simple_delete_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
            Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                ->simple_delete_all(database, collection, json_simple_query);
        }

        void simple_delete_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
            return Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                ->simple_delete_first(database, collection, json_simple_query);
        }

        std::vector<std::string> get_database_list() {
            return Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                ->get_database_list();
        }

        std::vector<std::string> get_collection_list(const std::string& database) {
            return Vortex::Core::CommonRuntime::Instance.get_storage()->get_backend()
                ->get_collection_list(database);
        }

        template<class Inspector>
        static void inspect(Inspector& i) {
            i.construct(&std::make_shared<Storage>);
            i.method("simple_insert", &Storage::simple_insert);
            i.method("simple_find_all", &Storage::simple_find_all);
            i.method("simple_find_first", &Storage::simple_find_first);
            i.method("simple_replace_first", &Storage::simple_replace_first);
            i.method("simple_delete_all", &Storage::simple_delete_all);
            i.method("simple_delete_first", &Storage::simple_delete_first);
            i.method("get_database_list", &Storage::get_database_list);
            i.method("get_collection_list", &Storage::get_collection_list);
        }
    };
}  // namespace duktape_bindings

DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::View);
DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::Router);
DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::Application);
DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::Storage);

#endif  // VORTEX_HAS_FEATURE_CRYPTOPP

namespace Vortex {
    namespace Core {
        namespace Script {
            Duktape::Duktape(Framework* framework) : framework_(framework) {
#ifdef VORTEX_HAS_FEATURE_DUKTAPE
                ctx_ = new duk::Context();
#endif
            }

            Duktape::~Duktape() {
#ifdef VORTEX_HAS_FEATURE_DUKTAPE
                if (ctx_ != nullptr) {
                    delete ctx_;
                }
#endif
            }

            void Duktape::setup() {
#ifdef VORTEX_HAS_FEATURE_DUKTAPE
                ctx_->registerClass<DuktapeBindings::View>();
                auto view = std::make_shared<DuktapeBindings::View>(framework_);
                ctx_->registerClass<DuktapeBindings::Router>();
                auto router = std::make_shared<DuktapeBindings::Router>(framework_);
                ctx_->registerClass<DuktapeBindings::Application>();
                auto application = std::make_shared<DuktapeBindings::Application>(framework_);
                ctx_->registerClass<DuktapeBindings::Storage>();
                auto storage = std::make_shared<DuktapeBindings::Storage>();

                ctx_->addGlobal("__view", view);
                ctx_->addGlobal("__router", router);
                ctx_->addGlobal("__application", application);
                ctx_->addGlobal("__storage", storage);

                exec("view=__view;router=__router;application=__application;storage=__storage;");
#endif
            }

            void Duktape::exec(std::string script) {
#ifdef VORTEX_HAS_FEATURE_DUKTAPE
                if (script.length() > 0) {
                    try {
                        ctx_->evalStringNoRes(script.c_str());
                    }
                    catch (duk::DuktapeException & e) {
                        std::string message = e.what();

                        

                        framework_->view_.echo("<i>Script error (duktape engine):</i><pre>" + message + "</pre>");
                        framework_->view_.respond();
                        framework_->exit();
                    }
                    catch (...) {
                        framework_->view_.echo("<i>Script error (duktape engine)</i>");
                        framework_->view_.respond();
                        framework_->exit();
                    }
                }
#else
                framework_->view_.echo("Script engine is unavailable.");
                framework_->view_.respond();
                framework_->exit();
#endif
            }
        }  // namespace Script
    }  // namespace Core
}  // namespace Vortex
