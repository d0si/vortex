#ifndef MAZE_MAZE_ARRAY_H
#define MAZE_MAZE_ARRAY_H

#include <string>
#include <vector>
#include <maze/maze_element.h>
#include <maze/maze_type.h>

namespace maze {

class maze_element;
class maze_object;

class maze_array {
 private:
  std::vector<maze_element> mazes_;
 public:
  maze_array* push(maze_element &maze);
  maze_array* push_maze(maze_element maze);
  maze_array operator<<(maze_element maze);
  maze_array* push(std::string value);
  maze_array operator<<(std::string value);
  maze_array* push(const char* value);
  maze_array operator<<(const char* value);
  maze_array* push(int value);
  maze_array operator<<(int value);
  maze_array* push(double value);
  maze_array operator<<(double value);
  maze_array* push(bool value);
  maze_array operator<<(bool value);
  maze_array* push(maze_array value);
  maze_array operator<<(maze_array value);
  maze_array* push(maze_array* value);
  maze_array operator<<(maze_array* value);
  maze_array* push(maze_object value);
  maze_array operator<<(maze_object value);
  maze_array* push(maze_object* value);
  maze_array operator<<(maze_object* value);

  maze_element get(int index, maze_type type);
  maze_element get(int index);
  maze_element operator[](int index);

  std::vector<maze_element>::iterator begin();
  std::vector<maze_element>::iterator end();

  std::vector<maze_element> get_mazes();

  int remove(int index);
  void clear();
  unsigned int size();

  bool is_empty();

  std::string to_json(int indentation_spacing = 2);

  static maze_array from_json(std::string json_string);
};

}  // namespace maze

#endif  // MAZE_MAZE_ARRAY_H
