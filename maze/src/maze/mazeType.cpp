#include "maze/mazeType.h"

namespace maze {

std::string toString(MazeType type) {
  switch (type) {
    case MazeType::Null:
      return "null";
    case MazeType::Bool:
      return "bool";
    case MazeType::Int:
      return "int";
    case MazeType::Double:
      return "double";
    case MazeType::String:
      return "string";
    case MazeType::Array:
      return "array";
    case MazeType::Object:
      return "object";
    default:
      return "unknown";
  }
}

}  // namespace maze
