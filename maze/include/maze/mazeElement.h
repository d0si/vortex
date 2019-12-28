#ifndef MAZE_MAZEELEMENT_H
#define MAZE_MAZEELEMENT_H

#include <string>
#include <memory>
#include "maze/mazeArray.h"
#include "maze/mazeObject.h"
#include "maze/mazeType.h"

namespace maze {

class MazeElement {
 private:
  MazeType type_ = MazeType::Null;

  bool valBool_;
  int valInt_;
  std::shared_ptr<double> ptrDouble_;
  std::shared_ptr<std::string> ptrString_;
  std::shared_ptr<MazeArray> ptrArray_;
  std::shared_ptr<MazeObject> ptrObject_;

  std::shared_ptr<std::string> ptrKey_;
 public:
  MazeElement();
  MazeElement(bool val);
  MazeElement(int val);
  MazeElement(double val);
  MazeElement(std::string& val);
  MazeElement(const char* val);
  MazeElement(MazeArray val);
  MazeElement(MazeObject val);
  MazeElement(MazeType val);
  ~MazeElement();

  void setType(MazeType type);
  MazeType getType();

  void setKey(std::string key);
  std::string getKey();

  void setNull();

  void setBool(bool val);
  void operator=(bool val);
  bool getBool();
  operator bool();

  void setInt(int val);
  void operator=(int val);
  int getInt();
  operator int();

  void setDouble(double val);
  void operator=(double val);
  double getDouble();
  operator double();

  void setString(std::string val);
  void operator=(std::string val);
  void operator=(const char* val);
  std::string getString();
  operator std::string();

  void setArray(MazeArray value);
  void operator=(MazeArray value);
  MazeArray getArray();
  operator MazeArray();

  void setObject(MazeObject value);
  void operator=(MazeObject value);
  MazeObject getObject();
  operator MazeObject();

  bool isNull();
  bool isBool();
  bool isInt();
  bool isDouble();
  bool isString();
  bool isArray();
  bool isObject();
  bool is(MazeType type);

  void apply(MazeElement newElement);

  std::string toJson(int indentationSpacing = 2);

  void applyJson(std::string jsonString);

  static MazeElement fromJson(std::string jsonString);
};

}  // namespace maze

#endif  // MAZE_MAZEELEMENT_H
