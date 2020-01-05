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
    i.construct(&std::make_shared<view>);
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
    i.construct(&std::make_shared<view>);
    i.method("get_id", &application::get_id);
    i.method("get_title", &application::get_title);
  }
};

}  // namespace duktape_bindings

DUK_CPP_DEF_CLASS_NAME(duktape_bindings::view);
DUK_CPP_DEF_CLASS_NAME(duktape_bindings::router);
DUK_CPP_DEF_CLASS_NAME(duktape_bindings::application);

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
  auto router = std::make_shared<duktape_bindings::router>(framework_);
  auto application = std::make_shared<duktape_bindings::application>(framework_);

  ctx_->addGlobal("__view", view);
  ctx_->addGlobal("__router", router);
  ctx_->addGlobal("__application", application);

  exec("view=__view;router=__router;");
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
