#include "maze/mazeArray.h"
#include "maze/helpers.h"

namespace maze {

MazeArray* MazeArray::push(MazeElement &maze) {
  mazes_.push_back(maze);

  return this;
}

MazeArray* MazeArray::pushMaze(MazeElement maze) {
  mazes_.push_back(maze);

  return this;
}

MazeArray MazeArray::operator<<(MazeElement maze) {
  pushMaze(maze);

  return *this;
}

MazeArray* MazeArray::push(std::string value) {
  return pushMaze(std::move(MazeElement(value)));
}

MazeArray MazeArray::operator<<(std::string value) {
  push(value);

  return *this;
}

MazeArray* MazeArray::push(const char* value) {
  return pushMaze(std::move(MazeElement(value)));
}

MazeArray MazeArray::operator<<(const char* value) {
  push(value);

  return *this;
}

MazeArray* MazeArray::push(int value) {
  return pushMaze(std::move(MazeElement(value)));
}

MazeArray MazeArray::operator<<(int value) {
  push(value);

  return *this;
}

MazeArray* MazeArray::push(double value) {
  return pushMaze(std::move(MazeElement(value)));
}

MazeArray MazeArray::operator<<(double value) {
  push(value);

  return *this;
}

MazeArray* MazeArray::push(bool value) {
  return pushMaze(std::move(MazeElement(value)));
}

MazeArray MazeArray::operator<<(bool value) {
  push(value);

  return *this;
}

MazeArray* MazeArray::push(MazeArray value) {
  return pushMaze(std::move(MazeElement(value)));
}

MazeArray MazeArray::operator<<(MazeArray value) {
  push(value);

  return *this;
}

MazeArray* MazeArray::push(MazeArray* value) {
  return pushMaze(std::move(MazeElement(value)));
}

MazeArray MazeArray::operator<<(MazeArray* value) {
  push(value);

  return *this;
}

MazeArray* MazeArray::push(MazeObject value) {
  return pushMaze(std::move(MazeElement(value)));
}

MazeArray MazeArray::operator<<(MazeObject value) {
  push(value);

  return *this;
}

MazeArray* MazeArray::push(MazeObject* value) {
  return pushMaze(std::move(MazeElement(value)));
}

MazeArray MazeArray::operator<<(MazeObject* value) {
  push(value);

  return *this;
}

MazeElement MazeArray::get(int index, MazeType type) {
  if ((unsigned int) index >= size()) {
    return MazeElement();
  }

  return mazes_[index];
}

MazeElement MazeArray::get(int index) {
  return get(index, MazeType::Bool);
}

MazeElement MazeArray::operator[](int index) {
  return get(index);
}

std::vector<MazeElement>::iterator MazeArray::begin() {
  return mazes_.begin();
}

std::vector<MazeElement>::iterator MazeArray::end() {
  return mazes_.end();
}

std::vector<MazeElement> MazeArray::getMazes() {
  return mazes_;
}

int MazeArray::remove(int index) {
  mazes_.erase(mazes_.begin() + index);
  return 0;
}

void MazeArray::clear() {
  mazes_.clear();
}

unsigned int MazeArray::size() {
  return (unsigned int) mazes_.size();
}

bool MazeArray::isEmpty() {
  return mazes_.empty();
}

std::string MazeArray::toJson(int indentationSpacing) {
  return array::toJsonArray(this).dump(indentationSpacing);
}

MazeArray MazeArray::fromJson(std::string jsonString) {
  return array::fromJson(nlohmann::json::parse(jsonString));
}

}  // namespace maze
