#ifndef MAZE_MAZE_ELEMENT_H
#define MAZE_MAZE_ELEMENT_H

#include <string>
#include <memory>
#include <maze/maze_array.h>
#include <maze/maze_object.h>
#include <maze/maze_type.h>

namespace maze {

class maze_element {
 private:
  maze_type type_ = maze_type::Null;

  bool val_bool_;
  int val_int_;
  std::shared_ptr<double> ptr_double_;
  std::shared_ptr<std::string> ptr_string_;
  std::shared_ptr<maze_array> ptr_array_;
  std::shared_ptr<maze_object> ptr_object_;

  std::shared_ptr<std::string> ptr_key_;
 public:
  maze_element();
  maze_element(bool val);
  maze_element(int val);
  maze_element(double val);
  maze_element(std::string& val);
  maze_element(const char* val);
  maze_element(maze_array val);
  maze_element(maze_object val);
  maze_element(maze_type val);
  ~maze_element();

  void set_type(maze_type type);
  maze_type get_type();

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

  void set_array(maze_array value);
  void operator=(maze_array value);
  maze_array get_array();
  operator maze_array();

  void set_object(maze_object value);
  void operator=(maze_object value);
  maze_object get_object();
  operator maze_object();

  bool is_null();
  bool is_bool();
  bool is_int();
  bool is_double();
  bool is_string();
  bool is_array();
  bool is_object();
  bool is(maze_type type);

  void apply(maze_element new_element);

  std::string to_json(int indentation_spacing = 2);

  void apply_json(std::string json_string);

  static maze_element from_json(std::string json_string);
};

}  // namespace maze

#endif  // MAZE_MAZE_ELEMENT_H
