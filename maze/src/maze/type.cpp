#include <maze/type.h>

namespace maze {

std::string to_string(type type) {
  switch (type) {
    case type::Null:
      return "null";
    case type::Bool:
      return "bool";
    case type::Int:
      return "int";
    case type::Double:
      return "double";
    case type::String:
      return "string";
    case type::Array:
      return "array";
    case type::Object:
      return "object";
    default:
      return "unknown";
  }
}

}  // namespace maze
