#include "maze/mazeObject.h"
#include "maze/helpers.h"

namespace maze {

MazeObject::MazeObject() {

}

MazeObject::MazeObject(std::string index) {
  insertNull(index);
}

MazeObject::MazeObject(std::string index, MazeElement &maze) {
  insert(index, maze);
}

MazeObject::MazeObject(std::string index, std::string value) {
  insert(index, value);
}

MazeObject::MazeObject(std::string index, const char* value) {
  insert(index, value);
}

MazeObject::MazeObject(std::string index, int value) {
  insert(index, value);
}

MazeObject::MazeObject(std::string index, double value) {
  insert(index, value);
}

MazeObject::MazeObject(std::string index, bool value) {
  insert(index, value);
}

MazeObject::MazeObject(std::string index, MazeArray value) {
  insert(index, value);
}

MazeObject::MazeObject(std::string index, MazeArray* value) {
  insert(index, value);
}

MazeObject::MazeObject(std::string index, MazeObject value) {
  insert(index, value);
}

MazeObject::MazeObject(std::string index, MazeObject* value) {
  insert(index, value);
}

MazeObject* MazeObject::set(std::string index, MazeElement &maze) {
  maze.setKey(index);
  int i = indexOf(index);
  if (i < 0) {
    return insert(index, maze);
  }

  mazes_[i] = make_pair(index, maze);

  return this;
}

MazeObject* MazeObject::setMaze(std::string index, MazeElement maze) {
  maze.setKey(index);
  int i = indexOf(index);
  if (i < 0) {
    return insert(index, maze);
  }

  mazes_[i] = std::make_pair(index, maze);

  return this;
}

MazeObject* MazeObject::set(std::string index, std::string value) {
  return setMaze(index, MazeElement(value));
}

MazeObject* MazeObject::set(std::string index, const char* value) {
  return setMaze(index, MazeElement(value));
}

MazeObject* MazeObject::set(std::string index, int value) {
  return setMaze(index, MazeElement(value));
}

MazeObject* MazeObject::set(std::string index, double value) {
  return setMaze(index, MazeElement(value));
}

MazeObject* MazeObject::set(std::string index, bool value) {
  return setMaze(index, MazeElement(value));
}

MazeObject* MazeObject::setNull(std::string index) {
  MazeElement el;
  el.setNull();

  return setMaze(index, el);
}

MazeObject* MazeObject::set(std::string index, MazeArray value) {
  return setMaze(index, MazeElement(value));
}

MazeObject* MazeObject::set(std::string index, MazeArray* value) {
  return setMaze(index, MazeElement(value));
}

MazeObject* MazeObject::set(std::string index, MazeObject value) {
  return setMaze(index, MazeElement(value));
}

MazeObject* MazeObject::set(std::string index, MazeObject* value) {
  return setMaze(index, MazeElement(value));
}

MazeObject* MazeObject::insert(std::string index, MazeElement &maze) {
  maze.setKey(index);
  mazes_.push_back(make_pair(index, maze));
  return this;
}

MazeObject* MazeObject::insertMaze(std::string index, MazeElement maze) {
  maze.setKey(index);
  mazes_.push_back(make_pair(index, maze));
  return this;
}

MazeObject* MazeObject::insert(std::string index, std::string value) {
  return insertMaze(index, MazeElement(value));
}

MazeObject* MazeObject::insert(std::string index, const char* value) {
  return insertMaze(index, MazeElement(value));
}

MazeObject* MazeObject::insert(std::string index, int value) {
  return insertMaze(index, MazeElement(value));
}

MazeObject* MazeObject::insert(std::string index, double value) {
  return insertMaze(index, MazeElement(value));
}

MazeObject* MazeObject::insert(std::string index, bool value) {
  return insertMaze(index, MazeElement(value));
}

MazeObject* MazeObject::insertNull(std::string index) {
  MazeElement el;
  el.setNull();

  return insertMaze(index, el);
}

MazeObject* MazeObject::insert(std::string index, MazeArray value) {
  return insertMaze(index, MazeElement(value));
}

MazeObject* MazeObject::insert(std::string index, MazeArray* value) {
  return insertMaze(index, MazeElement(value));
}

MazeObject* MazeObject::insert(std::string index, MazeObject value) {
  return insertMaze(index, MazeElement(value));
}

MazeObject* MazeObject::insert(std::string index, MazeObject* value) {
  return insertMaze(index, MazeElement(value));
}

MazeElement MazeObject::get(std::string index, MazeType type) {
  int i = indexOf(index);
  if (i < 0) {
    return MazeElement();
  }

  return mazes_[i].second;
}

MazeElement MazeObject::get(std::string index) {
  return get(index, MazeType::Bool);
}

MazeElement MazeObject::operator[](std::string index) {
  return get(index);
}

MazeElement MazeObject::operator[](int index) {
  if (index >= mazes_.size()) {
    return MazeElement();
  }

  return mazes_[index].second;
}

int MazeObject::remove(std::string index) {
  int i = indexOf(index);
  if (i < 0) {
    return -1;
  } else {
    mazes_.erase(mazes_.begin() + i);

    return 0;
  }
}

void MazeObject::clear() {
  mazes_.clear();
}

unsigned int MazeObject::size() {
  return (unsigned int) mazes_.size();
}

bool MazeObject::isEmpty() {
  return mazes_.empty();
}

std::vector<std::pair<std::string, MazeElement>>::iterator MazeObject::begin() {
  return mazes_.begin();
}

std::vector<std::pair<std::string, MazeElement>>::iterator MazeObject::end() {
  return mazes_.end();
}

std::vector<std::pair<std::string, MazeElement>> MazeObject::getMazes() {
  return mazes_;
}

int MazeObject::indexOf(std::string index) {
  if (mazes_.size() > 0) {
    for (int i = mazes_.size() - 1; i >= 0; --i) {
      if (mazes_[i].first == index) {
        return i;
      }
    }
  }

  return -1;
}

int MazeObject::firstIndexOf(std::string index) {
  for (unsigned int i = 0; i < mazes_.size(); ++i) {
    if (mazes_[i].first == index) {
      return i;
    }
  }

  return -1;
}

bool MazeObject::exists(std::string index) {
  return indexOf(index) >= 0;
}

bool MazeObject::isString(std::string index) {
  return (exists(index) && get(index).isString());
}

bool MazeObject::isInt(std::string index) {
  return (exists(index) && get(index).isInt());
}

bool MazeObject::isDouble(std::string index) {
  return (exists(index) && get(index).isDouble());
}

bool MazeObject::isBool(std::string index) {
  return (exists(index) && get(index).isBool());
}

bool MazeObject::isArray(std::string index) {
  return (exists(index) && get(index).isArray());
}

bool MazeObject::isObject(std::string index) {
  return (exists(index) && get(index).isObject());
}

void MazeObject::apply(MazeObject newObj) {
  for (auto maze : newObj) {
    if (exists(maze.first)) {
      get(maze.first).apply(maze.second);
    } else {
      insert(maze.first, maze.second);
    }
  }
}

std::string MazeObject::toJson(int indentationSpacing) {
  return object::toJsonObject(this).dump(indentationSpacing);
}

MazeObject MazeObject::fromJson(std::string jsonString) {
  return object::fromJson(nlohmann::json::parse(jsonString));
}

}  // namespace maze
