#pragma once

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace Engine {

struct AssetValue {
  using Object = std::unordered_map<std::string, AssetValue>;
  using Array = std::vector<AssetValue>;

  enum class Type { Null, String, Number, Boolean, Object, Array };

  Type type = Type::Null;

  std::string string;
  double number = 0.0;
  bool boolean = false;

  Object object;
  Array array;

  static AssetValue makeString(std::string value) {
    AssetValue result;
    result.type = Type::String;
    result.string = std::move(value);
    return result;
  }

  static AssetValue makeNumber(double value) {
    AssetValue result;
    result.type = Type::Number;
    result.number = value;
    return result;
  }

  static AssetValue makeBoolean(bool value) {
    AssetValue result;
    result.type = Type::Boolean;
    result.boolean = value;
    return result;
  }

  static AssetValue makeObject(Object value) {
    AssetValue result;
    result.type = Type::Object;
    result.object = std::move(value);
    return result;
  }

  static AssetValue makeArray(Array value) {
    AssetValue result;
    result.type = Type::Array;
    result.array = std::move(value);
    return result;
  }

  bool isString() const { return type == Type::String; }

  bool isNumber() const { return type == Type::Number; }

  bool isBoolean() const { return type == Type::Boolean; }

  bool isObject() const { return type == Type::Object; }

  bool isArray() const { return type == Type::Array; }

  const AssetValue &get(const std::string &key) const {
    if (!isObject())
      throw std::runtime_error("AssetValue is not an object");

    auto it = object.find(key);
    if (it == object.end())
      throw std::runtime_error("AssetValue: missing key '" + key + "'");

    return it->second;
  }
};

struct AssetData {
  std::unordered_map<std::string, AssetValue> sections;
};

} // namespace Engine
