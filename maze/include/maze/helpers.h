#ifndef MAZE_HELPERS_H
#define MAZE_HELPERS_H

#include <nlohmann/json.hpp>

namespace maze {

class element;
class array;
class object;
using json = nlohmann::json;

namespace helpers {
namespace element {

json to_json_element(maze::element* el);
void apply_json(maze::element* el, json json);
maze::element from_json(json json);

}  // namespace element
namespace array {

json to_json_array(maze::array* arr);
maze::array from_json(json json_array);

}  // namespace array
namespace object {

json to_json_object(maze::object* obj);
maze::object from_json(json json_object);

}  // namespace object
}  // namespace helpers
}  // namespace maze

#endif  // MAZE_HELPERS_H
