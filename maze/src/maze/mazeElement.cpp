#include "maze/mazeElement.h"
#include "maze/helpers.h"

namespace maze {

MazeElement::MazeElement() {

}

MazeElement::MazeElement(bool val) {
  setBool(val);
}

MazeElement::MazeElement(int val) {
  setInt(val);
}

MazeElement::MazeElement(double val) {
  setDouble(val);
}

MazeElement::MazeElement(std::string& val) {
  setString(val);
}

MazeElement::MazeElement(const char* val) {
  setString(val);
}

MazeElement::MazeElement(MazeArray val) {
  setArray(val);
}

MazeElement::MazeElement(MazeObject val) {
  setObject(val);
}

MazeElement::MazeElement(MazeType type) {
  setType(type);
}

MazeElement::~MazeElement() {
}

void MazeElement::setType(MazeType type) {
  switch (type) {
    case MazeType::Null:
      setNull();
      break;
    case MazeType::Bool:
      setBool(false);
      break;
    case MazeType::Int:
      setInt(0);
      break;
    case MazeType::Double:
      setDouble(0);
      break;
    case MazeType::String:
      setString("");
      break;
    case MazeType::Array:
      setArray(MazeArray());
      break;
    case MazeType::Object:
      setObject(MazeObject());
      break;
    default:
      setNull();
  }
}

MazeType MazeElement::getType() {
  return type_;
}

void MazeElement::setKey(std::string key) {
  ptrKey_ = std::make_shared<std::string>(key);
}

std::string MazeElement::getKey() {
  return *ptrKey_;
}

void MazeElement::setNull() {
  if (type_ != MazeType::Null) {
    valBool_ = false;
    valInt_ = 0;
    type_ = MazeType::Null;
  }
}

void MazeElement::setBool(bool val) {
  valBool_ = val;
  type_ = MazeType::Bool;
}

void MazeElement::operator=(bool val) {
  setBool(val);
}

bool MazeElement::getBool() {
  if (type_ == MazeType::Bool) {
    return valBool_;
  }
  return false;
}

MazeElement::operator bool() {
  return getBool();
}

void MazeElement::setInt(int val) {
  valInt_ = val;
  type_ = MazeType::Int;
}

void MazeElement::operator=(int val) {
  setInt(val);
}

int MazeElement::getInt() {
  if (type_ == MazeType::Int) {
    return valInt_;
  }

  return 0;
}

MazeElement::operator int() {
  return getInt();
}

void MazeElement::setDouble(double val) {
  ptrDouble_ = std::make_shared<double>(val);
  type_ = MazeType::Double;
}

void MazeElement::operator=(double val) {
  setDouble(val);
}

double MazeElement::getDouble() {
  if (type_ == MazeType::Double) {
    return *ptrDouble_;
  }

  return 0;
}

MazeElement::operator double() {
  return getDouble();
}

void MazeElement::setString(std::string val) {
  ptrString_ = std::make_shared<std::string>(val);
  type_ = MazeType::String;
}

void MazeElement::operator=(std::string val) {
  setString(val);
}

void MazeElement::operator=(const char* val) {
  setString(val);
}

std::string MazeElement::getString() {
  if (type_ == MazeType::String) {
    return *ptrString_;
  }

  return "";
}

MazeElement::operator std::string() {
  return getString();
}

void MazeElement::setArray(MazeArray val) {
  ptrArray_ = std::make_shared<MazeArray>(val);
  type_ = MazeType::Array;
}

void MazeElement::operator=(MazeArray val) {
  setArray(val);
}

MazeArray MazeElement::getArray() {
  if (type_ == MazeType::Array) {
    return *ptrArray_;
  }
  return MazeArray();
}

MazeElement::operator MazeArray() {
  return getArray();
}

void MazeElement::setObject(MazeObject val) {
  ptrObject_ = std::make_shared<MazeObject>(val);
  type_ = MazeType::Object;
}

void MazeElement::operator=(MazeObject val) {
  setObject(val);
}

MazeObject MazeElement::getObject() {
  if (type_ == MazeType::Object) {
    return *ptrObject_;
  }
  return MazeObject();
}

MazeElement::operator MazeObject() {
  return getObject();
}

bool MazeElement::isNull() {
  return is(MazeType::Null);
}

bool MazeElement::isBool() {
  return is(MazeType::Bool);
}

bool MazeElement::isInt() {
  return is(MazeType::Int);
}

bool MazeElement::isDouble() {
  return is(MazeType::Double);
}

bool MazeElement::isString() {
  return is(MazeType::String);
}

bool MazeElement::isArray() {
  return is(MazeType::Array);
}

bool MazeElement::isObject() {
  return is(MazeType::Object);
}

bool MazeElement::is(MazeType type) {
  return (type_ == type);
}

void MazeElement::apply(MazeElement newElement) {
  switch (newElement.getType()) {
    case MazeType::Null:
      setNull();
      break;
    case MazeType::Bool:
      setBool(newElement.getBool());
      break;
    case MazeType::Int:
      setInt(newElement.getInt());
      break;
    case MazeType::Double:
      setDouble(newElement.getDouble());
      break;
    case MazeType::String:
      setString(newElement.getString());
      break;
    case MazeType::Array:
      setArray(newElement.getArray());
      break;
    case MazeType::Object:
      getObject().apply(newElement.getObject());
      break;
  }
}

std::string MazeElement::toJson(int spacing) {
  return element::toJsonElement(this).dump(spacing);
}

void MazeElement::applyJson(std::string jsonString) {
  element::applyJson(this, nlohmann::json::parse(jsonString));
}

MazeElement MazeElement::fromJson(std::string jsonString) {
  return element::fromJson(nlohmann::json::parse(jsonString));
}

}  // namespace maze
