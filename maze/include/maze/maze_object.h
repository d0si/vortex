#ifndef MAZE_MAZE_OBJECT_H
#define MAZE_MAZE_OBJECT_H

#include <string>
#include <vector>
#include <maze/maze_element.h>
#include <maze/maze_type.h>

namespace maze {

class maze_element;
class maze_array;

class maze_object {
 private:
  std::vector<std::pair<std::string, maze_element>> mazes_;
 public:
  maze_object();
  maze_object(std::string index);
  maze_object(std::string index, maze_element &maze);
  maze_object(std::string index, std::string value);
  maze_object(std::string index, const char* value);
  maze_object(std::string index, int value);
  maze_object(std::string index, double value);
  maze_object(std::string index, bool value);
  maze_object(std::string index, maze_array value);
  maze_object(std::string index, maze_array* value);
  maze_object(std::string index, maze_object value);
  maze_object(std::string index, maze_object* value);

  maze_object* set(std::string index, maze_element &maze);
  maze_object* set_maze(std::string index, maze_element maze);
  maze_object* set(std::string index, std::string value);
  maze_object* set(std::string index, const char* value);
  maze_object* set(std::string index, int value);
  maze_object* set(std::string index, double value);
  maze_object* set(std::string index, bool value);
  maze_object* set(std::string index, maze_array value);
  maze_object* set(std::string index, maze_array* value);
  maze_object* set(std::string index, maze_object value);
  maze_object* set(std::string index, maze_object* value);
  maze_object* set_null(std::string index);

  maze_object* insert(std::string index, maze_element &maze);
  maze_object* insert_maze(std::string index, maze_element maze);
  maze_object* insert(std::string index, std::string value);
  maze_object* insert(std::string index, const char* value);
  maze_object* insert(std::string index, int value);
  maze_object* insert(std::string index, double value);
  maze_object* insert(std::string index, bool value);
  maze_object* insert(std::string index, maze_array value);
  maze_object* insert(std::string index, maze_array* value);
  maze_object* insert(std::string index, maze_object value);
  maze_object* insert(std::string index, maze_object* value);
  maze_object* insert_null(std::string index);

  maze_element get(std::string index, maze_type type);
  maze_element get(std::string index);
  maze_element operator[](std::string index);
  maze_element operator[](int index);

  int remove(std::string index);
  void clear();

  std::vector<std::pair<std::string, maze_element>>::iterator begin();
  std::vector<std::pair<std::string, maze_element>>::iterator end();

  std::vector<std::pair<std::string, maze_element>> get_mazes();

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

  void apply(maze_object new_obj);

  std::string to_json(int indentation_spacing = 2);

  static maze_object from_json(const std::string& json_string);
};

}  // namespace maze

#endif  // MAZE_MAZE_OBJECT_H
