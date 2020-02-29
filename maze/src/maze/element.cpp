#include <maze/element.h>
#include <maze/array.h>
#include <maze/object.h>
#include <maze/helpers.h>
#include <nlohmann/json.hpp>

namespace maze {

element::element() {

}

element::element(bool val) {
  set_bool(val);
}

element::element(int val) {
  set_int(val);
}

element::element(double val) {
  set_double(val);
}

element::element(std::string& val) {
  set_string(val);
}

element::element(const char* val) {
  set_string(val);
}

element::element(array val) {
  set_array(val);
}

element::element(object val) {
  set_object(val);
}

element::element(type type) {
  set_type(type);
}

element::~element() {
}

void element::set_type(type type) {
  switch (type) {
    case type::Null:
      set_null();
      break;
    case type::Bool:
      set_bool(false);
      break;
    case type::Int:
      set_int(0);
      break;
    case type::Double:
      set_double(0);
      break;
    case type::String:
      set_string("");
      break;
    case type::Array:
      set_array(array());
      break;
    case type::Object:
      set_object(object());
      break;
    default:
      set_null();
  }
}

type element::get_type() {
  return type_;
}

void element::set_key(std::string key) {
  ptr_key_ = std::make_shared<std::string>(key);
}

std::string element::get_key() {
  return *ptr_key_;
}

void element::set_null() {
  if (type_ != type::Null) {
    val_bool_ = false;
    val_int_ = 0;
    type_ = type::Null;
  }
}

void element::set_bool(bool val) {
  val_bool_ = val;
  type_ = type::Bool;
}

void element::operator=(bool val) {
  set_bool(val);
}

bool element::get_bool() {
  if (type_ == type::Bool) {
    return val_bool_;
  }
  return false;
}

element::operator bool() {
  return get_bool();
}

void element::set_int(int val) {
  val_int_ = val;
  type_ = type::Int;
}

void element::operator=(int val) {
  set_int(val);
}

int element::get_int() {
  if (type_ == type::Int) {
    return val_int_;
  }

  return 0;
}

element::operator int() {
  return get_int();
}

void element::set_double(double val) {
  ptr_double_ = std::make_shared<double>(val);
  type_ = type::Double;
}

void element::operator=(double val) {
  set_double(val);
}

double element::get_double() {
  if (type_ == type::Double) {
    return *ptr_double_;
  }

  return 0;
}

element::operator double() {
  return get_double();
}

void element::set_string(std::string val) {
  ptr_string_ = std::make_shared<std::string>(val);
  type_ = type::String;
}

void element::operator=(std::string val) {
  set_string(val);
}

void element::operator=(const char* val) {
  set_string(val);
}

std::string element::get_string() {
  if (type_ == type::String) {
    return *ptr_string_;
  }

  return "";
}

element::operator std::string() {
  return get_string();
}

void element::set_array(array val) {
  ptr_array_ = std::make_shared<array>(val);
  type_ = type::Array;
}

void element::operator=(array val) {
  set_array(val);
}

array element::get_array() {
  if (type_ == type::Array) {
    return *ptr_array_;
  }
  return array();
}

element::operator array() {
  return get_array();
}

void element::set_object(object val) {
  ptr_object_ = std::make_shared<object>(val);
  type_ = type::Object;
}

void element::operator=(object val) {
  set_object(val);
}

object element::get_object() {
  if (type_ == type::Object) {
    return *ptr_object_;
  }
  return object();
}

element::operator object() {
  return get_object();
}

bool element::is_null() {
  return is(type::Null);
}

bool element::is_bool() {
  return is(type::Bool);
}

bool element::is_int() {
  return is(type::Int);
}

bool element::is_double() {
  return is(type::Double);
}

bool element::is_string() {
  return is(type::String);
}

bool element::is_array() {
  return is(type::Array);
}

bool element::is_object() {
  return is(type::Object);
}

bool element::is(type type) {
  return (type_ == type);
}

void element::apply(element new_element) {
  switch (new_element.get_type()) {
    case type::Null:
      set_null();
      break;
    case type::Bool:
      set_bool(new_element.get_bool());
      break;
    case type::Int:
      set_int(new_element.get_int());
      break;
    case type::Double:
      set_double(new_element.get_double());
      break;
    case type::String:
      set_string(new_element.get_string());
      break;
    case type::Array:
      set_array(new_element.get_array());
      break;
    case type::Object:
      get_object().apply(new_element.get_object());
      break;
  }
}

std::string element::to_json(int spacing) {
  return helpers::element::to_json_element(this).dump(spacing);
}

void element::apply_json(std::string json_string) {
  helpers::element::apply_json(this, nlohmann::json::parse(json_string));
}

element element::from_json(std::string json_string) {
  return helpers::element::from_json(nlohmann::json::parse(json_string));
}

element element::get_null() {
  element el;
  el.set_null();
  return el;
}

}  // namespace maze
