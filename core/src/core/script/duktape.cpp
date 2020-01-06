#include <core/script/duktape.h>
#include <duktape-cpp/DuktapeCpp.h>
#include <core/framework/framework.h>

namespace duktape_bindings {

class view {
private:
  vortex::core::framework::framework *framework_;

public:
  view() {}

  view(vortex::core::framework::framework *framework) : framework_(framework) {}

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
  static void inspect(Inspector &i) {
    i.construct(&std::make_shared<view>);
    i.method("echo", &view::echo);
    i.method("set_template", &view::set_template);
    i.method("parse_template", &view::parse_template);
    i.method("set_page", &view::set_page);
    i.method("parse_page", &view::parse_page);
  }
};

class router {
private:
  vortex::core::framework::framework *framework_;

public:
  router() {}

  router(vortex::core::framework::framework *framework) : framework_(framework) {}

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
  static void inspect(Inspector &i) {
    i.construct(&std::make_shared<router>);
    i.method("get_hostname", &router::get_hostname);
    i.method("get_lang", &router::get_lang);
    i.method("get_controller", &router::get_controller);
  }
};

class application {
private:
  vortex::core::framework::framework *framework_;

public:
  application() {}

  application(vortex::core::framework::framework *framework) : framework_(framework) {}

  std::string get_id() {
    return framework_->application_.get_id();
  }

  std::string get_title() {
    return framework_->application_.get_title();
  }

  template<class Inspector>
  static void inspect(Inspector &i) {
    i.construct(&std::make_shared<application>);
    i.method("get_id", &application::get_id);
    i.method("get_title", &application::get_title);
  }
};

class collection {
private:
  vortex::core::framework::framework *framework_;
  std::string db_name_;
  std::string collection_name_;

public:
  collection() {}

  collection(vortex::core::framework::framework *framework, std::string db_name, std::string collection_name)
          : framework_(framework), db_name_(db_name), collection_name_(collection_name) {}

  template<class Inspector>
  static void inspect(Inspector &i) {
    i.construct(&std::make_shared<collection>);
  }
};

class db {
private:
  vortex::core::framework::framework *framework_;
  std::string db_name_;

public:
  db() {}

  db(vortex::core::framework::framework *framework, std::string db_name)
          : framework_(framework), db_name_(db_name) {}

  template<class Inspector>
  static void inspect(Inspector &i) {
    i.construct(&std::make_shared<db>);
  }
};

class mongo {
private:
  vortex::core::framework::framework *framework_;

public:
  mongo() {}

  mongo(vortex::core::framework::framework *framework) : framework_(framework) {}

  std::string get_default_db_name() {
    return framework_->mongo_.get_default_db_name();
  }

  std::vector<std::string> list_databases() {
    return framework_->mongo_.list_databases();
  }

  std::vector<std::string> list_collections(std::string database_name) {
    return framework_->mongo_.list_collections(database_name);
  }

  db get_db(std::string database_name) {
    return db(framework_, database_name);
  }

  collection get_collection(std::string collection_name) {
    return get_collection(get_default_db_name(), collection_name);
  }

  collection get_collection(std::string database_name, std::string collection_name) {
    return collection(framework_, database_name, collection_name);
  }

  void drop_database(std::string database_name) {
    framework_->mongo_.drop_database(database_name);
  }

  void clone_database(std::string old_name, std::string new_name) {
    framework_->mongo_.clone_database(old_name, new_name);
  }

  template<class Inspector>
  static void inspect(Inspector &i) {
    i.construct(&std::make_shared<mongo>);
    i.method("get_default_db_name", &mongo::get_default_db_name);
    i.method("list_databases", &mongo::list_databases);
    i.method("list_collections", &mongo::list_collections);
    i.method("get_db", &mongo::get_db);
    // i.method("get_collection", &mongo::get_collection);
    i.method("drop_database", &mongo::drop_database);
    i.method("clone_database", &mongo::clone_database);
  }
};

}  // namespace duktape_bindings

DUK_CPP_DEF_CLASS_NAME(duktape_bindings::view);
DUK_CPP_DEF_CLASS_NAME(duktape_bindings::router);
DUK_CPP_DEF_CLASS_NAME(duktape_bindings::application);
DUK_CPP_DEF_CLASS_NAME(duktape_bindings::mongo);
DUK_CPP_DEF_CLASS_NAME(duktape_bindings::db);
DUK_CPP_DEF_CLASS_NAME(duktape_bindings::collection);

namespace vortex {
namespace core {
namespace script {
duktape::duktape(framework::framework* framework) : framework_(framework) {
  ctx_ = new duk::Context();
}

duktape::~duktape() {
  delete ctx_;
}

void duktape::setup() {
  ctx_->registerClass<duktape_bindings::view>();
  auto view = std::make_shared<duktape_bindings::view>(framework_);
  ctx_->registerClass<duktape_bindings::router>();
  auto router = std::make_shared<duktape_bindings::router>(framework_);
  ctx_->registerClass<duktape_bindings::application>();
  auto application = std::make_shared<duktape_bindings::application>(framework_);
  ctx_->registerClass<duktape_bindings::mongo>();
  ctx_->registerClass<duktape_bindings::db>();
  ctx_->registerClass<duktape_bindings::collection>();
  auto mongo = std::make_shared<duktape_bindings::mongo>(framework_);

  ctx_->addGlobal("__view", view);
  ctx_->addGlobal("__router", router);
  ctx_->addGlobal("__application", application);
  ctx_->addGlobal("__mongo", mongo);

  exec("view=__view;router=__router;application=__application;mongo=__mongo;");
}

void duktape::exec(std::string script) {
  if (script.length() > 0) {
    try {
      ctx_->evalStringNoRes(script.c_str());
    } catch (duk::DuktapeException &e) {
      std::string message = e.what();
      framework_->view_.echo("<i>Script error (duktape engine):</i><pre>" + message + "</pre>");
      framework_->view_.respond();
      framework_->exit();
    } catch (...) {
      framework_->view_.echo("<i>Script error (duktape engine)</i>");
      framework_->view_.respond();
      framework_->exit();
    }
  }
}

}  // namespace script
}  // namespace core
}  // namespace vortex