#include <maze/maze_type.h>

namespace maze {

std::string to_string(maze_type type) {
  switch (type) {
    case maze_type::Null:
      return "null";
    case maze_type::Bool:
      return "bool";
    case maze_type::Int:
      return "int";
    case maze_type::Double:
      return "double";
    case maze_type::String:
      return "string";
    case maze_type::Array:
      return "array";
    case maze_type::Object:
      return "object";
    default:
      return "unknown";
  }
}

}  // namespace maze
