#include <Core/Script/Duktape.h>
#ifdef VORTEX_HAS_FEATURE_DUKTAPE
#include <duktape-cpp/DuktapeCpp.h>
#endif
#include <Core/Framework.h>

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

		void set_template(std::string name) {
			framework_->view_.set_template(name);
		}

		void parse_template() {
			framework_->view_.parse_template();
		}

		void set_page(std::string name) {
			framework_->view_.set_page(name);
		}

		void parse_page() {
			framework_->view_.parse_page();
		}

		template<class Inspector>
		static void inspect(Inspector& i) {
			i.construct(&std::make_shared<View>);
			i.method("echo", &View::echo);
			i.method("set_template", &View::set_template);
			i.method("parse_template", &View::parse_template);
			i.method("set_page", &View::set_page);
			i.method("parse_page", &View::parse_page);
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

		template<class Inspector>
		static void inspect(Inspector& i) {
			i.construct(&std::make_shared<Router>);
			i.method("get_hostname", &Router::get_hostname);
			i.method("get_lang", &Router::get_lang);
			i.method("get_controller", &Router::get_controller);
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

	/*class Collection {
	private:
		Vortex::Core::Framework* framework_;
		std::string db_name_;
		std::string collection_name_;

	public:
		Collection() {}

		Collection(Vortex::Core::Framework* framework, std::string db_name, std::string collection_name)
			: framework_(framework), db_name_(db_name), collection_name_(collection_name) {}

		template<class Inspector>
		static void inspect(Inspector& i) {
			i.construct(&std::make_shared<Collection>);
		}
	};

	class Db {
	private:
		Vortex::Core::Framework* framework_;
		std::string db_name_;

	public:
		Db() {}

		Db(Vortex::Core::Framework* framework, std::string db_name)
			: framework_(framework), db_name_(db_name) {}

		template<class Inspector>
		static void inspect(Inspector& i) {
			i.construct(&std::make_shared<Db>);
		}
	};

	class Mongo {
	private:
		Vortex::Core::Framework* framework_;

	public:
		Mongo() {}

		Mongo(Vortex::Core::Framework* framework) : framework_(framework) {}

		std::string get_default_db_name() {
			return framework_->mongo_.get_default_db_name();
		}

		std::vector<std::string> list_databases() {
			return framework_->mongo_.list_databases();
		}

		std::vector<std::string> list_collections(std::string database_name) {
			return framework_->mongo_.list_collections(database_name);
		}

		Db get_db(std::string database_name) {
			return Db(framework_, database_name);
		}

		Collection get_collection(std::string collection_name) {
			return get_collection(get_default_db_name(), collection_name);
		}

		Collection get_collection(std::string database_name, std::string collection_name) {
			return Collection(framework_, database_name, collection_name);
		}

		void drop_database(std::string database_name) {
			framework_->mongo_.drop_database(database_name);
		}

		void clone_database(std::string old_name, std::string new_name) {
			framework_->mongo_.clone_database(old_name, new_name);
		}

		template<class Inspector>
		static void inspect(Inspector& i) {
			i.construct(&std::make_shared<Mongo>);
			i.method("get_default_db_name", &Mongo::get_default_db_name);
			i.method("list_databases", &Mongo::list_databases);
			i.method("list_collections", &Mongo::list_collections);
			i.method("get_db", &Mongo::get_db);
			// i.method("get_collection", &Mongo::get_collection);
			i.method("drop_database", &Mongo::drop_database);
			i.method("clone_database", &Mongo::clone_database);
		}
	};*/
}  // namespace duktape_bindings

DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::View);
DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::Router);
DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::Application);
/*DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::Mongo);
DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::Db);
DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::Collection);*/

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
				/*ctx_->registerClass<DuktapeBindings::Mongo>();
				ctx_->registerClass<DuktapeBindings::Db>();
				ctx_->registerClass<DuktapeBindings::Collection>();
				auto mongo = std::make_shared<DuktapeBindings::Mongo>(framework_);*/

				ctx_->addGlobal("__view", view);
				ctx_->addGlobal("__router", router);
				ctx_->addGlobal("__application", application);
				// ctx_->addGlobal("__mongo", mongo);

				exec("view=__view;router=__router;application=__application;mongo=__mongo;");
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
#endif
			}
		}  // namespace Script
	}  // namespace Core
}  // namespace Vortex
