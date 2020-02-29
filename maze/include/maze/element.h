#ifndef MAZE_ELEMENT_H
#define MAZE_ELEMENT_H

#include <string>
#include <memory>
#include <maze/type.h>

namespace maze {

class array;
class object;

class element {
 private:
  type type_ = type::Null;

  bool val_bool_;
  int val_int_;
  std::shared_ptr<double> ptr_double_;
  std::shared_ptr<std::string> ptr_string_;
  std::shared_ptr<array> ptr_array_;
  std::shared_ptr<object> ptr_object_;

  std::shared_ptr<std::string> ptr_key_;
 public:
  element();
  element(bool val);
  element(int val);
  element(double val);
  element(std::string& val);
  element(const char* val);
  element(array val);
  element(object val);
  element(type val);
  ~element();

  void set_type(type type);
  type get_type();

  void set_key(std::string key);
  std::string get_key();

  void set_null();

  void set_bool(bool val);
  void operator=(bool val);
  bool get_bool();
  operator bool();

  void set_int(int val);
  void operator=(int val);
  int get_int();
  operator int();

  void set_double(double val);
  void operator=(double val);
  double get_double();
  operator double();

  void set_string(std::string val);
  void operator=(std::string val);
  void operator=(const char* val);
  std::string get_string();
  operator std::string();

  void set_array(array value);
  void operator=(array value);
  array get_array();
  operator array();

  void set_object(object value);
  void operator=(object value);
  object get_object();
  operator object();

  bool is_null();
  bool is_bool();
  bool is_int();
  bool is_double();
  bool is_string();
  bool is_array();
  bool is_object();
  bool is(type type);

  void apply(element new_element);

  std::string to_json(int indentation_spacing = 2);

  void apply_json(std::string json_string);

  static element from_json(std::string json_string);

  static element get_null();
};

}  // namespace maze

#endif  // MAZE_ELEMENT_H
