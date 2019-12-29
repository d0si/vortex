#include <maze/maze_object.h>
#include <maze/helpers.h>

namespace maze {

maze_object::maze_object() {

}

maze_object::maze_object(std::string index) {
  insert_null(index);
}

maze_object::maze_object(std::string index, maze_element &maze) {
  insert(index, maze);
}

maze_object::maze_object(std::string index, std::string value) {
  insert(index, value);
}

maze_object::maze_object(std::string index, const char* value) {
  insert(index, value);
}

maze_object::maze_object(std::string index, int value) {
  insert(index, value);
}

maze_object::maze_object(std::string index, double value) {
  insert(index, value);
}

maze_object::maze_object(std::string index, bool value) {
  insert(index, value);
}

maze_object::maze_object(std::string index, maze_array value) {
  insert(index, value);
}

maze_object::maze_object(std::string index, maze_array* value) {
  insert(index, value);
}

maze_object::maze_object(std::string index, maze_object value) {
  insert(index, value);
}

maze_object::maze_object(std::string index, maze_object* value) {
  insert(index, value);
}

maze_object* maze_object::set(std::string index, maze_element &maze) {
  maze.set_key(index);
  int i = index_of(index);
  if (i < 0) {
    return insert(index, maze);
  }

  mazes_[i] = make_pair(index, maze);

  return this;
}

maze_object* maze_object::set_maze(std::string index, maze_element maze) {
  maze.set_key(index);
  int i = index_of(index);
  if (i < 0) {
    return insert(index, maze);
  }

  mazes_[i] = std::make_pair(index, maze);

  return this;
}

maze_object* maze_object::set(std::string index, std::string value) {
  return set_maze(index, maze_element(value));
}

maze_object* maze_object::set(std::string index, const char* value) {
  return set_maze(index, maze_element(value));
}

maze_object* maze_object::set(std::string index, int value) {
  return set_maze(index, maze_element(value));
}

maze_object* maze_object::set(std::string index, double value) {
  return set_maze(index, maze_element(value));
}

maze_object* maze_object::set(std::string index, bool value) {
  return set_maze(index, maze_element(value));
}

maze_object* maze_object::set_null(std::string index) {
  maze_element el;
  el.set_null();

  return set_maze(index, el);
}

maze_object* maze_object::set(std::string index, maze_array value) {
  return set_maze(index, maze_element(value));
}

maze_object* maze_object::set(std::string index, maze_array* value) {
  return set_maze(index, maze_element(value));
}

maze_object* maze_object::set(std::string index, maze_object value) {
  return set_maze(index, maze_element(value));
}

maze_object* maze_object::set(std::string index, maze_object* value) {
  return set_maze(index, maze_element(value));
}

maze_object* maze_object::insert(std::string index, maze_element &maze) {
  maze.set_key(index);
  mazes_.push_back(make_pair(index, maze));

  return this;
}

maze_object* maze_object::insert_maze(std::string index, maze_element maze) {
  maze.set_key(index);
  mazes_.push_back(make_pair(index, maze));

  return this;
}

maze_object* maze_object::insert(std::string index, std::string value) {
  return insert_maze(index, maze_element(value));
}

maze_object* maze_object::insert(std::string index, const char* value) {
  return insert_maze(index, maze_element(value));
}

maze_object* maze_object::insert(std::string index, int value) {
  return insert_maze(index, maze_element(value));
}

maze_object* maze_object::insert(std::string index, double value) {
  return insert_maze(index, maze_element(value));
}

maze_object* maze_object::insert(std::string index, bool value) {
  return insert_maze(index, maze_element(value));
}

maze_object* maze_object::insert_null(std::string index) {
  maze_element el;
  el.set_null();

  return insert_maze(index, el);
}

maze_object* maze_object::insert(std::string index, maze_array value) {
  return insert_maze(index, maze_element(value));
}

maze_object* maze_object::insert(std::string index, maze_array* value) {
  return insert_maze(index, maze_element(value));
}

maze_object* maze_object::insert(std::string index, maze_object value) {
  return insert_maze(index, maze_element(value));
}

maze_object* maze_object::insert(std::string index, maze_object* value) {
  return insert_maze(index, maze_element(value));
}

maze_element maze_object::get(std::string index, maze_type type) {
  int i = index_of(index);
  if (i < 0) {
    return maze_element();
  }

  return mazes_[i].second;
}

maze_element maze_object::get(std::string index) {
  return get(index, maze_type::Bool);
}

maze_element maze_object::operator[](std::string index) {
  return get(index);
}

maze_element maze_object::operator[](int index) {
  if (index >= mazes_.size()) {
    return maze_element();
  }

  return mazes_[index].second;
}

int maze_object::remove(std::string index) {
  int i = index_of(index);
  if (i < 0) {
    return -1;
  } else {
    mazes_.erase(mazes_.begin() + i);

    return 0;
  }
}

void maze_object::clear() {
  mazes_.clear();
}

unsigned int maze_object::size() {
  return (unsigned int) mazes_.size();
}

bool maze_object::is_empty() {
  return mazes_.empty();
}

std::vector<std::pair<std::string, maze_element>>::iterator maze_object::begin() {
  return mazes_.begin();
}

std::vector<std::pair<std::string, maze_element>>::iterator maze_object::end() {
  return mazes_.end();
}

std::vector<std::pair<std::string, maze_element>> maze_object::get_mazes() {
  return mazes_;
}

int maze_object::index_of(std::string index) {
  if (mazes_.size() > 0) {
    for (int i = mazes_.size() - 1; i >= 0; --i) {
      if (mazes_[i].first == index) {
        return i;
      }
    }
  }

  return -1;
}

int maze_object::first_index_of(std::string index) {
  for (unsigned int i = 0; i < mazes_.size(); ++i) {
    if (mazes_[i].first == index) {
      return i;
    }
  }

  return -1;
}

bool maze_object::exists(std::string index) {
  return index_of(index) >= 0;
}

bool maze_object::is_string(std::string index) {
  return (exists(index) && get(index).is_string());
}

bool maze_object::is_int(std::string index) {
  return (exists(index) && get(index).is_int());
}

bool maze_object::is_double(std::string index) {
  return (exists(index) && get(index).is_double());
}

bool maze_object::is_bool(std::string index) {
  return (exists(index) && get(index).is_bool());
}

bool maze_object::is_array(std::string index) {
  return (exists(index) && get(index).is_array());
}

bool maze_object::is_object(std::string index) {
  return (exists(index) && get(index).is_object());
}

void maze_object::apply(maze_object new_obj) {
  for (auto maze : new_obj) {
    if (exists(maze.first)) {
      get(maze.first).apply(maze.second);
    } else {
      insert(maze.first, maze.second);
    }
  }
}

std::string maze_object::to_json(int indentation_spacing) {
  return object::to_json_object(this).dump(indentation_spacing);
}

maze_object maze_object::from_json(const std::string& json_string) {
  return object::from_json(nlohmann::json::parse(json_string));
}

}  // namespace maze
