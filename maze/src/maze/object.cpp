#include <maze/object.h>
#include <maze/element.h>
#include <maze/array.h>
#include <maze/helpers.h>
#include <nlohmann/json.hpp>

namespace maze {

object::object() {

}

object::object(std::string index) {
  insert_null(index);
}

object::object(std::string index, element maze) {
  insert(index, maze);
}

object::object(std::string index, std::string value) {
  insert(index, value);
}

object::object(std::string index, const char* value) {
  insert(index, value);
}

object::object(std::string index, int value) {
  insert(index, value);
}

object::object(std::string index, double value) {
  insert(index, value);
}

object::object(std::string index, bool value) {
  insert(index, value);
}

object::object(std::string index, array value) {
  insert(index, value);
}

object::object(std::string index, array* value) {
  insert(index, value);
}

object::object(std::string index, object value) {
  insert(index, value);
}

object::object(std::string index, object* value) {
  insert(index, value);
}

object* object::set(std::string index, element &maze) {
  maze.set_key(index);
  int i = index_of(index);
  if (i < 0) {
    return insert(index, maze);
  }

  mazes_[i] = make_pair(index, maze);

  return this;
}

object* object::set_maze(std::string index, element maze) {
  maze.set_key(index);
  int i = index_of(index);
  if (i < 0) {
    return insert(index, maze);
  }

  mazes_[i] = std::make_pair(index, maze);

  return this;
}

object* object::set(std::string index, std::string value) {
  return set_maze(index, element(value));
}

object* object::set(std::string index, const char* value) {
  return set_maze(index, element(value));
}

object* object::set(std::string index, int value) {
  return set_maze(index, element(value));
}

object* object::set(std::string index, double value) {
  return set_maze(index, element(value));
}

object* object::set(std::string index, bool value) {
  return set_maze(index, element(value));
}

object* object::set_null(std::string index) {
  element el;
  el.set_null();

  return set_maze(index, el);
}

object* object::set(std::string index, array value) {
  return set_maze(index, element(value));
}

object* object::set(std::string index, array* value) {
  return set_maze(index, element(value));
}

object* object::set(std::string index, object value) {
  return set_maze(index, element(value));
}

object* object::set(std::string index, object* value) {
  return set_maze(index, element(value));
}

object* object::insert(std::string index, element &maze) {
  maze.set_key(index);
  mazes_.push_back(make_pair(index, maze));

  return this;
}

object* object::insert_maze(std::string index, element maze) {
  maze.set_key(index);
  mazes_.push_back(make_pair(index, maze));

  return this;
}

object* object::insert(std::string index, std::string value) {
  return insert_maze(index, element(value));
}

object* object::insert(std::string index, const char* value) {
  return insert_maze(index, element(value));
}

object* object::insert(std::string index, int value) {
  return insert_maze(index, element(value));
}

object* object::insert(std::string index, double value) {
  return insert_maze(index, element(value));
}

object* object::insert(std::string index, bool value) {
  return insert_maze(index, element(value));
}

object* object::insert_null(std::string index) {
  element el;
  el.set_null();

  return insert_maze(index, el);
}

object* object::insert(std::string index, array value) {
  return insert_maze(index, element(value));
}

object* object::insert(std::string index, array* value) {
  return insert_maze(index, element(value));
}

object* object::insert(std::string index, object value) {
  return insert_maze(index, element(value));
}

object* object::insert(std::string index, object* value) {
  return insert_maze(index, element(value));
}

element object::get(std::string index, type type) {
  int i = index_of(index);
  if (i < 0) {
    return element();
  }

  return mazes_[i].second;
}

element object::get(std::string index) {
  return get(index, type::Bool);
}

element object::operator[](std::string index) {
  return get(index);
}

element object::operator[](int index) {
  if (index >= mazes_.size()) {
    return element();
  }

  return mazes_[index].second;
}

int object::remove(std::string index) {
  int i = index_of(index);
  if (i < 0) {
    return -1;
  } else {
    mazes_.erase(mazes_.begin() + i);

    return 0;
  }
}

void object::clear() {
  mazes_.clear();
}

unsigned int object::size() {
  return (unsigned int) mazes_.size();
}

bool object::is_empty() {
  return mazes_.empty();
}

std::vector<std::pair<std::string, element>>::iterator object::begin() {
  return mazes_.begin();
}

std::vector<std::pair<std::string, element>>::iterator object::end() {
  return mazes_.end();
}

std::vector<std::pair<std::string, element>> object::get_mazes() {
  return mazes_;
}

int object::index_of(std::string index) {
  if (mazes_.size() > 0) {
    for (int i = mazes_.size() - 1; i >= 0; --i) {
      if (mazes_[i].first == index) {
        return i;
      }
    }
  }

  return -1;
}

int object::first_index_of(std::string index) {
  for (unsigned int i = 0; i < mazes_.size(); ++i) {
    if (mazes_[i].first == index) {
      return i;
    }
  }

  return -1;
}

bool object::exists(std::string index) {
  return index_of(index) >= 0;
}

bool object::is_string(std::string index) {
  return (exists(index) && get(index).is_string());
}

bool object::is_int(std::string index) {
  return (exists(index) && get(index).is_int());
}

bool object::is_double(std::string index) {
  return (exists(index) && get(index).is_double());
}

bool object::is_bool(std::string index) {
  return (exists(index) && get(index).is_bool());
}

bool object::is_array(std::string index) {
  return (exists(index) && get(index).is_array());
}

bool object::is_object(std::string index) {
  return (exists(index) && get(index).is_object());
}

void object::apply(object new_obj) {
  for (auto maze : new_obj) {
    if (exists(maze.first)) {
      get(maze.first).apply(maze.second);
    } else {
      insert(maze.first, maze.second);
    }
  }
}

std::string object::to_json(int indentation_spacing) {
  return helpers::object::to_json_object(this).dump(indentation_spacing);
}

object object::from_json(const std::string& json_string) {
  return helpers::object::from_json(nlohmann::json::parse(json_string));
}

}  // namespace maze
