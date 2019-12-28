#ifndef MAZE_HELPERS_H
#define MAZE_HELPERS_H

#include <nlohmann/json.hpp>
#include "maze/mazeElement.h"

namespace maze {
namespace element {

nlohmann::json toJsonElement(MazeElement* element);
void applyJson(MazeElement* element, nlohmann::json json);
MazeElement fromJson(nlohmann::json json);

}  // namespace element
namespace array {

nlohmann::json toJsonArray(MazeArray* array);
MazeArray fromJson(nlohmann::json jsonArray);

}  // namespace array
namespace object {

nlohmann::json toJsonObject(MazeObject* object);
MazeObject fromJson(nlohmann::json jsonObject);

}  // namespace object
}  // namespace maze

#endif  // MAZE_HELPERS_H
