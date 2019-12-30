#ifndef MAZE_HELPERS_H
#define MAZE_HELPERS_H

#include <nlohmann/json.hpp>
#include <maze/element.h>

namespace maze {
namespace helpers {
namespace element {

nlohmann::json to_json_element(maze::element* el);
void apply_json(maze::element* el, nlohmann::json json);
maze::element from_json(nlohmann::json json);

}  // namespace element
namespace array {

nlohmann::json to_json_array(maze::array* arr);
maze::array from_json(nlohmann::json json_array);

}  // namespace array
namespace object {

nlohmann::json to_json_object(maze::object* obj);
maze::object from_json(nlohmann::json json_object);

}  // namespace object
}  // namespace helpers
}  // namespace maze

#endif  // MAZE_HELPERS_H
