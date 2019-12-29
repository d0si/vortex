#ifndef MAZE_MAZE_TYPE_H
#define MAZE_MAZE_TYPE_H

#include <string>

namespace maze {

enum class maze_type {
  Null = 0,
  Bool = 1,
  Int = 2,
  Double = 3,
  String = 4,
  Array = 5,
  Object = 6
};

std::string to_string(maze_type type);

}  // namespace maze

#endif  // MAZE_MAZE_TYPE_H
