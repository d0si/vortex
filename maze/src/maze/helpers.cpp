#include <maze/helpers.h>

namespace maze {
namespace element {

nlohmann::json to_json_element(maze_element* element) {
  nlohmann::json el;

  switch (element->get_type()) {
    case maze_type::Null:
      break;
    case maze_type::Bool:
      el = element->get_bool();
      break;
    case maze_type::Int:
      el = element->get_int();
      break;
    case maze_type::Double:
      el = element->get_double();
      break;
    case maze_type::String:
      el = element->get_string();
      break;
    case maze_type::Array: {
      maze_array array = element->get_array();
      el = array::to_json_array(&array);
      break;
    }
    case maze_type::Object: {
      maze_object object = element->get_object();
      el = object::to_json_object(&object);
      break;
    }
  }

  return el;
}

void apply_json(maze_element* element, nlohmann::json json) {
  element->apply(from_json(json));
}

maze_element from_json(nlohmann::json json) {
  maze_element el;

  if (json.is_boolean()) {
    el = json.get<bool>();
  } else if (json.is_number_integer()) {
    el = json.get<int>();
  } else if (json.is_number_float()) {
    el = json.get<double>();
  } else if (json.is_string()) {
    el = json.get<std::string>();
  } else if (json.is_array()) {
    el = array::from_json(json);
  } else if (json.is_object()) {
    el = object::from_json(json);
  } else if (json.is_null()) {
    el.set_null();
  }

  return el;
}

}  // namespace element
namespace array {

nlohmann::json to_json_array(maze_array* array) {
  nlohmann::json arr = nlohmann::json::array();

  auto mazes = array->get_mazes();
  for (unsigned int i = 0; i < mazes.size(); i++) {
    maze_element maze = mazes[i];
    switch (maze.get_type()) {
      case maze_type::String:
        arr.push_back(maze.get_string());
        break;
      case maze_type::Int:
        arr.push_back(maze.get_int());
        break;
      case maze_type::Double:
        arr.push_back(maze.get_double());
        break;
      case maze_type::Bool:
        arr.push_back(maze.get_bool());
        break;
      case maze_type::Null:
        arr.push_back(nullptr);
        break;
      case maze_type::Array: {
        maze_array array = maze.get_array();
        arr.push_back(array::to_json_array(&array));
        break;
      }
      case maze_type::Object: {
        maze_object object = maze.get_object();
        arr.push_back(object::to_json_object(&object));
        break;
      }
    }
  }

  return arr;
}

maze_array from_json(nlohmann::json json_array) {
  maze_array arr;

  for (auto it = json_array.begin(); it != json_array.end(); it++) {
    if (it->is_string()) {
      arr.push(it->get<std::string>());
    } else if (it->is_number_integer()) {
      arr.push(it->get<int>());
    } else if (it->is_number_float()) {
      arr.push(it->get<double>());
    } else if (it->is_boolean()) {
      arr.push(it->get<bool>());
    } else if (it->is_array()) {
      arr.push(array::from_json(*it));
    } else if (it->is_object()) {
      arr.push(object::from_json(*it));
    } else if (it->is_null()) {
      arr.push_maze(maze_element(maze_type::Null));
    }
  }

  return arr;
}

}  // namespace array
namespace object {

nlohmann::json to_json_object(maze_object* object) {
  nlohmann::json obj = nlohmann::json::object();
  auto mazes = object->get_mazes();

  for (auto m : mazes) {
    std::string index = m.first;
    auto maze = m.second;

    switch (maze.get_type()) {
      case maze_type::String:
        obj[index] = maze.get_string();
        break;
      case maze_type::Int:
        obj[index] = maze.get_int();
        break;
      case maze_type::Double:
        obj[index] = maze.get_double();
        break;
      case maze_type::Bool:
        obj[index] = maze.get_bool();
        break;
      case maze_type::Null:
        obj[index] = nullptr;
        break;
      case maze_type::Array: {
        maze_array array = maze.get_array();
        obj[index] = array::to_json_array(&array);
        break;
      }
      case maze_type::Object: {
        maze_object object = maze.get_object();
        obj[index] = object::to_json_object(&object);
        break;
      }
    }
  }

  return obj;
}

maze_object from_json(nlohmann::json json_object) {
  maze_object obj;

  for (auto it = json_object.begin(); it != json_object.end(); it++) {
    if (it->is_string()) {
      obj.set(it.key(), it->get<std::string>());
    } else if (it->is_number_integer()) {
      obj.set(it.key(), it->get<int>());
    } else if (it->is_number_float()) {
      obj.set(it.key(), it->get<double>());
    } else if (it->is_boolean()) {
      obj.set(it.key(), it->get<bool>());
    } else if (it->is_array()) {
      obj.set(it.key(), array::from_json(*it));
    } else if (it->is_object()) {
      obj.set(it.key(), object::from_json(*it));
    } else if (it->is_null()) {
      obj.set_maze(it.key(), maze_element(maze_type::Null));
    }
  }

  return obj;
}

} // namespace object
}  // namespace maze
