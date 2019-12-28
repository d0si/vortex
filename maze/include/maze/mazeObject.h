#ifndef MAZE_MAZEOBJECT_H
#define MAZE_MAZEOBJECT_H

#include <string>
#include <vector>
#include "maze/mazeElement.h"

namespace maze {

class MazeObject {
 private:
  std::vector<std::pair<std::string, MazeElement>> mazes_;
 public:
  MazeObject();
  MazeObject(std::string index);
  MazeObject(std::string index, MazeElement &maze);
  MazeObject(std::string index, std::string value);
  MazeObject(std::string index, const char* value);
  MazeObject(std::string index, int value);
  MazeObject(std::string index, double value);
  MazeObject(std::string index, bool value);
  MazeObject(std::string index, MazeArray value);
  MazeObject(std::string index, MazeArray* value);
  MazeObject(std::string index, MazeObject value);
  MazeObject(std::string index, MazeObject* value);

  MazeObject* set(std::string index, MazeElement &maze);
  MazeObject* setMaze(std::string index, MazeElement maze);
  MazeObject* set(std::string index, std::string value);
  MazeObject* set(std::string index, const char* value);
  MazeObject* set(std::string index, int value);
  MazeObject* set(std::string index, double value);
  MazeObject* set(std::string index, bool value);
  MazeObject* set(std::string index, MazeArray value);
  MazeObject* set(std::string index, MazeArray* value);
  MazeObject* set(std::string index, MazeObject value);
  MazeObject* set(std::string index, MazeObject* value);
  MazeObject* setNull(std::string index);

  MazeObject* insert(std::string index, MazeElement &maze);
  MazeObject* insertMaze(std::string index, MazeElement maze);
  MazeObject* insert(std::string index, std::string value);
  MazeObject* insert(std::string index, const char* value);
  MazeObject* insert(std::string index, int value);
  MazeObject* insert(std::string index, double value);
  MazeObject* insert(std::string index, bool value);
  MazeObject* insert(std::string index, MazeArray value);
  MazeObject* insert(std::string index, MazeArray* value);
  MazeObject* insert(std::string index, MazeObject value);
  MazeObject* insert(std::string index, MazeObject* value);
  MazeObject* insertNull(std::string index);

  MazeElement get(std::string index, MazeType type);
  MazeElement get(std::string index);
  MazeElement operator[](std::string index);
  MazeElement operator[](int index);

  int remove(std::string index);
  void clear();

  std::vector<std::pair<std::string, MazeElement>>::iterator begin();
  std::vector<std::pair<std::string, MazeElement>>::iterator end();

  std::vector<std::pair<std::string, MazeElement>> getMazes();

  int indexOf(std::string index);
  int firstIndexOf(std::string index);
  bool exists(std::string index);
  unsigned int size();
  bool isEmpty();

  bool isString(std::string index);
  bool isInt(std::string index);
  bool isDouble(std::string index);
  bool isBool(std::string index);
  bool isArray(std::string index);
  bool isObject(std::string index);

  void apply(MazeObject newObj);

  std::string toJson(int indentationSpacing = 2);

  static MazeObject fromJson(std::string jsonString);
};

}  // namespace maze

#endif  // MAZE_MAZEOBJECT_H
