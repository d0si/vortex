#ifndef MAZE_HELPERS_H
#define MAZE_HELPERS_H

#include <nlohmann/json.hpp>
#include <maze/maze_element.h>

namespace maze {
namespace element {

nlohmann::json to_json_element(maze_element* element);
void apply_json(maze_element* element, nlohmann::json json);
maze_element from_json(nlohmann::json json);

}  // namespace element
namespace array {

nlohmann::json to_json_array(maze_array* array);
maze_array from_json(nlohmann::json json_array);

}  // namespace array
namespace object {

nlohmann::json to_json_object(maze_object* object);
maze_object from_json(nlohmann::json json_object);

}  // namespace object
}  // namespace maze

#endif  // MAZE_HELPERS_H
