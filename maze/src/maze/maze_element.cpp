#include <maze/maze_element.h>
#include <maze/helpers.h>

namespace maze {

maze_element::maze_element() {

}

maze_element::maze_element(bool val) {
  set_bool(val);
}

maze_element::maze_element(int val) {
  set_int(val);
}

maze_element::maze_element(double val) {
  set_double(val);
}

maze_element::maze_element(std::string& val) {
  set_string(val);
}

maze_element::maze_element(const char* val) {
  set_string(val);
}

maze_element::maze_element(maze_array val) {
  set_array(val);
}

maze_element::maze_element(maze_object val) {
  set_object(val);
}

maze_element::maze_element(maze_type type) {
  set_type(type);
}

maze_element::~maze_element() {
}

void maze_element::set_type(maze_type type) {
  switch (type) {
    case maze_type::Null:
      set_null();
      break;
    case maze_type::Bool:
      set_bool(false);
      break;
    case maze_type::Int:
      set_int(0);
      break;
    case maze_type::Double:
      set_double(0);
      break;
    case maze_type::String:
      set_string("");
      break;
    case maze_type::Array:
      set_array(maze_array());
      break;
    case maze_type::Object:
      set_object(maze_object());
      break;
    default:
      set_null();
  }
}

maze_type maze_element::get_type() {
  return type_;
}

void maze_element::set_key(std::string key) {
  ptr_key_ = std::make_shared<std::string>(key);
}

std::string maze_element::get_key() {
  return *ptr_key_;
}

void maze_element::set_null() {
  if (type_ != maze_type::Null) {
    val_bool_ = false;
    val_int_ = 0;
    type_ = maze_type::Null;
  }
}

void maze_element::set_bool(bool val) {
  val_bool_ = val;
  type_ = maze_type::Bool;
}

void maze_element::operator=(bool val) {
  set_bool(val);
}

bool maze_element::get_bool() {
  if (type_ == maze_type::Bool) {
    return val_bool_;
  }
  return false;
}

maze_element::operator bool() {
  return get_bool();
}

void maze_element::set_int(int val) {
  val_int_ = val;
  type_ = maze_type::Int;
}

void maze_element::operator=(int val) {
  set_int(val);
}

int maze_element::get_int() {
  if (type_ == maze_type::Int) {
    return val_int_;
  }

  return 0;
}

maze_element::operator int() {
  return get_int();
}

void maze_element::set_double(double val) {
  ptr_double_ = std::make_shared<double>(val);
  type_ = maze_type::Double;
}

void maze_element::operator=(double val) {
  set_double(val);
}

double maze_element::get_double() {
  if (type_ == maze_type::Double) {
    return *ptr_double_;
  }

  return 0;
}

maze_element::operator double() {
  return get_double();
}

void maze_element::set_string(std::string val) {
  ptr_string_ = std::make_shared<std::string>(val);
  type_ = maze_type::String;
}

void maze_element::operator=(std::string val) {
  set_string(val);
}

void maze_element::operator=(const char* val) {
  set_string(val);
}

std::string maze_element::get_string() {
  if (type_ == maze_type::String) {
    return *ptr_string_;
  }

  return "";
}

maze_element::operator std::string() {
  return get_string();
}

void maze_element::set_array(maze_array val) {
  ptr_array_ = std::make_shared<maze_array>(val);
  type_ = maze_type::Array;
}

void maze_element::operator=(maze_array val) {
  set_array(val);
}

maze_array maze_element::get_array() {
  if (type_ == maze_type::Array) {
    return *ptr_array_;
  }
  return maze_array();
}

maze_element::operator maze_array() {
  return get_array();
}

void maze_element::set_object(maze_object val) {
  ptr_object_ = std::make_shared<maze_object>(val);
  type_ = maze_type::Object;
}

void maze_element::operator=(maze_object val) {
  set_object(val);
}

maze_object maze_element::get_object() {
  if (type_ == maze_type::Object) {
    return *ptr_object_;
  }
  return maze_object();
}

maze_element::operator maze_object() {
  return get_object();
}

bool maze_element::is_null() {
  return is(maze_type::Null);
}

bool maze_element::is_bool() {
  return is(maze_type::Bool);
}

bool maze_element::is_int() {
  return is(maze_type::Int);
}

bool maze_element::is_double() {
  return is(maze_type::Double);
}

bool maze_element::is_string() {
  return is(maze_type::String);
}

bool maze_element::is_array() {
  return is(maze_type::Array);
}

bool maze_element::is_object() {
  return is(maze_type::Object);
}

bool maze_element::is(maze_type type) {
  return (type_ == type);
}

void maze_element::apply(maze_element new_element) {
  switch (new_element.get_type()) {
    case maze_type::Null:
      set_null();
      break;
    case maze_type::Bool:
      set_bool(new_element.get_bool());
      break;
    case maze_type::Int:
      set_int(new_element.get_int());
      break;
    case maze_type::Double:
      set_double(new_element.get_double());
      break;
    case maze_type::String:
      set_string(new_element.get_string());
      break;
    case maze_type::Array:
      set_array(new_element.get_array());
      break;
    case maze_type::Object:
      get_object().apply(new_element.get_object());
      break;
  }
}

std::string maze_element::to_json(int spacing) {
  return element::to_json_element(this).dump(spacing);
}

void maze_element::apply_json(std::string json_string) {
  element::apply_json(this, nlohmann::json::parse(json_string));
}

maze_element maze_element::from_json(std::string json_string) {
  return element::from_json(nlohmann::json::parse(json_string));
}

}  // namespace maze
