#ifndef MAZE_OBJECT_H
#define MAZE_OBJECT_H

#include <string>
#include <vector>
#include <maze/element.h>

namespace maze {

class object {
 private:
  std::vector<std::pair<std::string, element>> mazes_;
 public:
  object();
  object(std::string index);
  object(std::string index, element maze);
  object(std::string index, std::string value);
  object(std::string index, const char* value);
  object(std::string index, int value);
  object(std::string index, double value);
  object(std::string index, bool value);
  object(std::string index, array value);
  object(std::string index, array* value);
  object(std::string index, object value);
  object(std::string index, object* value);

  object* set(std::string index, element &maze);
  object* set_maze(std::string index, element maze);
  object* set(std::string index, std::string value);
  object* set(std::string index, const char* value);
  object* set(std::string index, int value);
  object* set(std::string index, double value);
  object* set(std::string index, bool value);
  object* set(std::string index, array value);
  object* set(std::string index, array* value);
  object* set(std::string index, object value);
  object* set(std::string index, object* value);
  object* set_null(std::string index);

  object* insert(std::string index, element &maze);
  object* insert_maze(std::string index, element maze);
  object* insert(std::string index, std::string value);
  object* insert(std::string index, const char* value);
  object* insert(std::string index, int value);
  object* insert(std::string index, double value);
  object* insert(std::string index, bool value);
  object* insert(std::string index, array value);
  object* insert(std::string index, array* value);
  object* insert(std::string index, object value);
  object* insert(std::string index, object* value);
  object* insert_null(std::string index);

  element get(std::string index, type type);
  element get(std::string index);
  element operator[](std::string index);
  element operator[](int index);

  int remove(std::string index);
  void clear();

  std::vector<std::pair<std::string, element>>::iterator begin();
  std::vector<std::pair<std::string, element>>::iterator end();

  std::vector<std::pair<std::string, element>> get_mazes();

  int index_of(std::string index);
  int first_index_of(std::string index);
  bool exists(std::string index);
  unsigned int size();
  bool is_empty();

  bool is_string(std::string index);
  bool is_int(std::string index);
  bool is_double(std::string index);
  bool is_bool(std::string index);
  bool is_array(std::string index);
  bool is_object(std::string index);

  void apply(object new_obj);

  std::string to_json(int indentation_spacing = 2);

  static object from_json(const std::string& json_string);
};

}  // namespace maze

#endif  // MAZE_OBJECT_H
