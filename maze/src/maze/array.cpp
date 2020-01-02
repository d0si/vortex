#include <maze/array.h>
#include <maze/element.h>
#include <maze/object.h>
#include <maze/helpers.h>
#include <nlohmann/json.hpp>

namespace maze {

array* array::push(element &maze) {
  mazes_.push_back(maze);

  return this;
}

array* array::push_maze(element maze) {
  mazes_.push_back(maze);

  return this;
}

array array::operator<<(element maze) {
  push_maze(maze);

  return *this;
}

array* array::push(std::string value) {
  return push_maze(std::move(element(value)));
}

array array::operator<<(std::string value) {
  push(value);

  return *this;
}

array* array::push(const char* value) {
  return push_maze(std::move(element(value)));
}

array array::operator<<(const char* value) {
  push(value);

  return *this;
}

array* array::push(int value) {
  return push_maze(std::move(element(value)));
}

array array::operator<<(int value) {
  push(value);

  return *this;
}

array* array::push(double value) {
  return push_maze(std::move(element(value)));
}

array array::operator<<(double value) {
  push(value);

  return *this;
}

array* array::push(bool value) {
  return push_maze(std::move(element(value)));
}

array array::operator<<(bool value) {
  push(value);

  return *this;
}

array* array::push(array value) {
  return push_maze(std::move(element(value)));
}

array array::operator<<(array value) {
  push(value);

  return *this;
}

array* array::push(array* value) {
  return push_maze(std::move(element(value)));
}

array array::operator<<(array* value) {
  push(value);

  return *this;
}

array* array::push(object value) {
  return push_maze(std::move(element(value)));
}

array array::operator<<(object value) {
  push(value);

  return *this;
}

array* array::push(object* value) {
  return push_maze(std::move(element(value)));
}

array array::operator<<(object* value) {
  push(value);

  return *this;
}

element array::get(int index, type type) {
  if ((unsigned int) index >= size()) {
    return element();
  }

  return mazes_[index];
}

element array::get(int index) {
  return get(index, type::Bool);
}

element array::operator[](int index) {
  return get(index);
}

std::vector<element>::iterator array::begin() {
  return mazes_.begin();
}

std::vector<element>::iterator array::end() {
  return mazes_.end();
}

std::vector<element> array::get_mazes() {
  return mazes_;
}

int array::remove(int index) {
  mazes_.erase(mazes_.begin() + index);
  return 0;
}

void array::clear() {
  mazes_.clear();
}

unsigned int array::size() {
  return (unsigned int) mazes_.size();
}

bool array::is_empty() {
  return mazes_.empty();
}

std::string array::to_json(int indentation_spacing) {
  return helpers::array::to_json_array(this).dump(indentation_spacing);
}

array array::from_json(std::string json_string) {
  return helpers::array::from_json(nlohmann::json::parse(json_string));
}

}  // namespace maze
