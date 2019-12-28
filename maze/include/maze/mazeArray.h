#ifndef MAZE_MAZEARRAY_H
#define MAZE_MAZEARRAY_H

#include <string>
#include <vector>
#include "maze/mazeElement.h"

namespace maze {

class MazeArray {
 private:
  std::vector<MazeElement> mazes_;
 public:
  MazeArray* push(MazeElement &maze);
  MazeArray* pushMaze(MazeElement maze);
  MazeArray operator<<(MazeElement maze);
  MazeArray* push(std::string value);
  MazeArray operator<<(std::string value);
  MazeArray* push(const char* value);
  MazeArray operator<<(const char* value);
  MazeArray* push(int value);
  MazeArray operator<<(int value);
  MazeArray* push(double value);
  MazeArray operator<<(double value);
  MazeArray* push(bool value);
  MazeArray operator<<(bool value);
  MazeArray* push(MazeArray value);
  MazeArray operator<<(MazeArray value);
  MazeArray* push(MazeArray* value);
  MazeArray operator<<(MazeArray* value);
  MazeArray* push(MazeObject value);
  MazeArray operator<<(MazeObject value);
  MazeArray* push(MazeObject* value);
  MazeArray operator<<(MazeObject* value);

  MazeElement get(int index, MazeType type);
  MazeElement get(int index);
  MazeElement operator[](int index);

  std::vector<MazeElement>::iterator begin();
  std::vector<MazeElement>::iterator end();

  std::vector<MazeElement> getMazes();

  int remove(int index);
  void clear();
  unsigned int size();

  bool isEmpty();

  std::string toJson(int indentationSpacing = 2);

  static MazeArray fromJson(std::string jsonString);
};

}  // namespace maze

#endif  // MAZE_MAZEARRAY_H
