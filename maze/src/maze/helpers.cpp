#include <maze/helpers.h>
#include <maze/element.h>
#include <maze/array.h>
#include <maze/object.h>

namespace maze {
namespace helpers {
namespace element {

json to_json_element(maze::element* el) {
  json json_el;

  switch (el->get_type()) {
    case type::Null:
      break;
    case type::Bool:
      json_el = el->get_bool();
      break;
    case type::Int:
      json_el = el->get_int();
      break;
    case type::Double:
      json_el = el->get_double();
      break;
    case type::String:
      json_el = el->get_string();
      break;
    case type::Array: {
      maze::array arr = el->get_array();
      json_el = helpers::array::to_json_array(&arr);
      break;
    }
    case type::Object: {
      maze::object obj = el->get_object();
      json_el = helpers::object::to_json_object(&obj);
      break;
    }
  }

  return json_el;
}

void apply_json(maze::element* el, json json) {
  el->apply(from_json(json));
}

maze::element from_json(json json) {
  maze::element el;

  if (json.is_boolean()) {
    el = json.get<bool>();
  } else if (json.is_number_integer()) {
    el = json.get<int>();
  } else if (json.is_number_float()) {
    el = json.get<double>();
  } else if (json.is_string()) {
    el = json.get<std::string>();
  } else if (json.is_array()) {
    el = helpers::array::from_json(json);
  } else if (json.is_object()) {
    el = helpers::object::from_json(json);
  } else if (json.is_null()) {
    el.set_null();
  }

  return el;
}

}  // namespace element
namespace array {

json to_json_array(maze::array* array) {
  json json_arr = json::array();

  auto mazes = array->get_mazes();
  for (unsigned int i = 0; i < mazes.size(); i++) {
    maze::element maze = mazes[i];
    switch (maze.get_type()) {
      case type::String:
        json_arr.push_back(maze.get_string());
        break;
      case type::Int:
        json_arr.push_back(maze.get_int());
        break;
      case type::Double:
        json_arr.push_back(maze.get_double());
        break;
      case type::Bool:
        json_arr.push_back(maze.get_bool());
        break;
      case type::Null:
        json_arr.push_back(nullptr);
        break;
      case type::Array: {
        maze::array arr = maze.get_array();
        json_arr.push_back(helpers::array::to_json_array(&arr));
        break;
      }
      case type::Object: {
        maze::object obj = maze.get_object();
        json_arr.push_back(helpers::object::to_json_object(&obj));
        break;
      }
    }
  }

  return json_arr;
}

maze::array from_json(json json_array) {
  maze::array arr;

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
      arr.push(helpers::array::from_json(*it));
    } else if (it->is_object()) {
      arr.push(helpers::object::from_json(*it));
    } else if (it->is_null()) {
      arr.push_maze(maze::element(type::Null));
    }
  }

  return arr;
}

}  // namespace array
namespace object {

json to_json_object(maze::object* object) {
  json json_obj = json::object();
  auto mazes = object->get_mazes();

  for (auto m : mazes) {
    std::string index = m.first;
    auto maze = m.second;

    switch (maze.get_type()) {
      case type::String:
        json_obj[index] = maze.get_string();
        break;
      case type::Int:
        json_obj[index] = maze.get_int();
        break;
      case type::Double:
        json_obj[index] = maze.get_double();
        break;
      case type::Bool:
        json_obj[index] = maze.get_bool();
        break;
      case type::Null:
        json_obj[index] = nullptr;
        break;
      case type::Array: {
        maze::array arr = maze.get_array();
        json_obj[index] = helpers::array::to_json_array(&arr);
        break;
      }
      case type::Object: {
        maze::object obj = maze.get_object();
        json_obj[index] = helpers::object::to_json_object(&obj);
        break;
      }
    }
  }

  return json_obj;
}

maze::object from_json(json json_object) {
  maze::object obj;

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
      obj.set(it.key(), helpers::array::from_json(*it));
    } else if (it->is_object()) {
      obj.set(it.key(), helpers::object::from_json(*it));
    } else if (it->is_null()) {
      obj.set_maze(it.key(), maze::element(type::Null));
    }
  }

  return obj;
}

}  // namespace object
}  // namespace helpers
}  // namespace maze
