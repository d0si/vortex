#ifndef MAZE_MAZETYPE_H
#define MAZE_MAZETYPE_H

#include <string>

namespace maze {

enum MazeType {
  Null,
  Bool,
  Int,
  Double,
  String,
  Array,
  Object
};

std::string toString(MazeType type);

}  // namespace maze

#endif  // MAZE_MAZETYPE_H
