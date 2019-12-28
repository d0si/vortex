#include "maze/helpers.h"

namespace maze {
namespace element {

nlohmann::json toJsonElement(MazeElement* element) {
  nlohmann::json el;

  switch (element->getType()) {
    case MazeType::Null:
      break;
    case MazeType::Bool:
      el = element->getBool();
      break;
    case MazeType::Int:
      el = element->getInt();
      break;
    case MazeType::Double:
      el = element->getDouble();
      break;
    case MazeType::String:
      el = element->getString();
      break;
    case MazeType::Array: {
      MazeArray array = element->getArray();
      el = array::toJsonArray(&array);
      break;
    }
    case MazeType::Object: {
      MazeObject object = element->getObject();
      el = object::toJsonObject(&object);
      break;
    }
  }

  return el;
}

void applyJson(MazeElement* element, nlohmann::json json) {
  element->apply(fromJson(json));
}

MazeElement fromJson(nlohmann::json json) {
  MazeElement el;

  if (json.is_boolean()) {
    el = json.get<bool>();
  } else if (json.is_number_integer()) {
    el = json.get<int>();
  } else if (json.is_number_float()) {
    el = json.get<double>();
  } else if (json.is_string()) {
    el = json.get<std::string>();
  } else if (json.is_array()) {
    el = array::fromJson(json);
  } else if (json.is_object()) {
    el = object::fromJson(json);
  } else if (json.is_null()) {
    el.setNull();
  }

  return el;
}

}  // namespace element
namespace array {

nlohmann::json toJsonArray(MazeArray* array) {
  nlohmann::json arr = nlohmann::json::array();

  auto mazes = array->getMazes();
  for (unsigned int i = 0; i < mazes.size(); i++) {
    MazeElement maze = mazes[i];
    switch (maze.getType()) {
      case MazeType::String:
        arr.push_back(maze.getString());
        break;
      case MazeType::Int:
        arr.push_back(maze.getInt());
        break;
      case MazeType::Double:
        arr.push_back(maze.getDouble());
        break;
      case MazeType::Bool:
        arr.push_back(maze.getBool());
        break;
      case MazeType::Null:
        arr.push_back(nullptr);
        break;
      case MazeType::Array: {
        MazeArray array = maze.getArray();
        arr.push_back(array::toJsonArray(&array));
        break;
      }
      case MazeType::Object: {
        MazeObject object = maze.getObject();
        arr.push_back(object::toJsonObject(&object));
        break;
      }
    }
  }

  return arr;
}

MazeArray fromJson(nlohmann::json jsonArray) {
  MazeArray arr;

  for (auto it = jsonArray.begin(); it != jsonArray.end(); it++) {
    if (it->is_string()) {
      arr.push(it->get<std::string>());
    } else if (it->is_number_integer()) {
      arr.push(it->get<int>());
    } else if (it->is_number_float()) {
      arr.push(it->get<double>());
    } else if (it->is_boolean()) {
      arr.push(it->get<bool>());
    } else if (it->is_array()) {
      arr.push(array::fromJson(*it));
    } else if (it->is_object()) {
      arr.push(object::fromJson(*it));
    } else if (it->is_null()) {
      arr.pushMaze(MazeElement(MazeType::Null));
    }
  }

  return arr;
}

}  // namespace array
namespace object {

nlohmann::json toJsonObject(MazeObject* object) {
  nlohmann::json obj = nlohmann::json::object();
  auto mazes = object->getMazes();

  for (auto m : mazes) {
    std::string index = m.first;
    auto maze = m.second;

    switch (maze.getType()) {
      case MazeType::String:
        obj[index] = maze.getString();
        break;
      case MazeType::Int:
        obj[index] = maze.getInt();
        break;
      case MazeType::Double:
        obj[index] = maze.getDouble();
        break;
      case MazeType::Bool:
        obj[index] = maze.getBool();
        break;
      case MazeType::Null:
        obj[index] = nullptr;
        break;
      case MazeType::Array: {
        MazeArray array = maze.getArray();
        obj[index] = array::toJsonArray(&array);
        break;
      }
      case MazeType::Object: {
        MazeObject object = maze.getObject();
        obj[index] = object::toJsonObject(&object);
        break;
      }
    }
  }

  return obj;
}

MazeObject fromJson(nlohmann::json jsonObject) {
  MazeObject obj;

  for (auto it = jsonObject.begin(); it != jsonObject.end(); it++) {
    if (it->is_string()) {
      obj.set(it.key(), it->get<std::string>());
    } else if (it->is_number_integer()) {
      obj.set(it.key(), it->get<int>());
    } else if (it->is_number_float()) {
      obj.set(it.key(), it->get<double>());
    } else if (it->is_boolean()) {
      obj.set(it.key(), it->get<bool>());
    } else if (it->is_array()) {
      obj.set(it.key(), array::fromJson(*it));
    } else if (it->is_object()) {
      obj.set(it.key(), object::fromJson(*it));
    } else if (it->is_null()) {
      obj.setMaze(it.key(), MazeElement(MazeType::Null));
    }
  }

  return obj;
}

} // namespace object
}  // namespace maze
