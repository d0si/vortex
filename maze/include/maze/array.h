#ifndef MAZE_ARRAY_H
#define MAZE_ARRAY_H

#include <string>
#include <vector>
#include <maze/element.h>

namespace maze {

class array {
 private:
  std::vector<element> mazes_;
 public:
  array* push(element &maze);
  array* push_maze(element maze);
  array operator<<(element maze);
  array* push(std::string value);
  array operator<<(std::string value);
  array* push(const char* value);
  array operator<<(const char* value);
  array* push(int value);
  array operator<<(int value);
  array* push(double value);
  array operator<<(double value);
  array* push(bool value);
  array operator<<(bool value);
  array* push(array value);
  array operator<<(array value);
  array* push(array* value);
  array operator<<(array* value);
  array* push(object value);
  array operator<<(object value);
  array* push(object* value);
  array operator<<(object* value);

  element get(int index, type type);
  element get(int index);
  element operator[](int index);

  std::vector<element>::iterator begin();
  std::vector<element>::iterator end();

  std::vector<element> get_mazes();

  int remove(int index);
  void clear();
  unsigned int size();

  bool is_empty();

  std::string to_json(int indentation_spacing = 2);

  static array from_json(std::string json_string);
};

}  // namespace maze

#endif  // MAZE_ARRAY_H
