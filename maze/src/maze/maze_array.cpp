#include <maze/maze_array.h>
#include <maze/helpers.h>

namespace maze {

maze_array* maze_array::push(maze_element &maze) {
  mazes_.push_back(maze);

  return this;
}

maze_array* maze_array::push_maze(maze_element maze) {
  mazes_.push_back(maze);

  return this;
}

maze_array maze_array::operator<<(maze_element maze) {
  push_maze(maze);

  return *this;
}

maze_array* maze_array::push(std::string value) {
  return push_maze(std::move(maze_element(value)));
}

maze_array maze_array::operator<<(std::string value) {
  push(value);

  return *this;
}

maze_array* maze_array::push(const char* value) {
  return push_maze(std::move(maze_element(value)));
}

maze_array maze_array::operator<<(const char* value) {
  push(value);

  return *this;
}

maze_array* maze_array::push(int value) {
  return push_maze(std::move(maze_element(value)));
}

maze_array maze_array::operator<<(int value) {
  push(value);

  return *this;
}

maze_array* maze_array::push(double value) {
  return push_maze(std::move(maze_element(value)));
}

maze_array maze_array::operator<<(double value) {
  push(value);

  return *this;
}

maze_array* maze_array::push(bool value) {
  return push_maze(std::move(maze_element(value)));
}

maze_array maze_array::operator<<(bool value) {
  push(value);

  return *this;
}

maze_array* maze_array::push(maze_array value) {
  return push_maze(std::move(maze_element(value)));
}

maze_array maze_array::operator<<(maze_array value) {
  push(value);

  return *this;
}

maze_array* maze_array::push(maze_array* value) {
  return push_maze(std::move(maze_element(value)));
}

maze_array maze_array::operator<<(maze_array* value) {
  push(value);

  return *this;
}

maze_array* maze_array::push(maze_object value) {
  return push_maze(std::move(maze_element(value)));
}

maze_array maze_array::operator<<(maze_object value) {
  push(value);

  return *this;
}

maze_array* maze_array::push(maze_object* value) {
  return push_maze(std::move(maze_element(value)));
}

maze_array maze_array::operator<<(maze_object* value) {
  push(value);

  return *this;
}

maze_element maze_array::get(int index, maze_type type) {
  if ((unsigned int) index >= size()) {
    return maze_element();
  }

  return mazes_[index];
}

maze_element maze_array::get(int index) {
  return get(index, maze_type::Bool);
}

maze_element maze_array::operator[](int index) {
  return get(index);
}

std::vector<maze_element>::iterator maze_array::begin() {
  return mazes_.begin();
}

std::vector<maze_element>::iterator maze_array::end() {
  return mazes_.end();
}

std::vector<maze_element> maze_array::get_mazes() {
  return mazes_;
}

int maze_array::remove(int index) {
  mazes_.erase(mazes_.begin() + index);
  return 0;
}

void maze_array::clear() {
  mazes_.clear();
}

unsigned int maze_array::size() {
  return (unsigned int) mazes_.size();
}

bool maze_array::is_empty() {
  return mazes_.empty();
}

std::string maze_array::to_json(int indentation_spacing) {
  return array::to_json_array(this).dump(indentation_spacing);
}

maze_array maze_array::from_json(std::string json_string) {
  return array::from_json(nlohmann::json::parse(json_string));
}

}  // namespace maze
