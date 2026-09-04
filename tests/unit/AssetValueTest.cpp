#include <catch2/catch_test_macros.hpp>

#include <engine/assets/AssetData.hpp>

TEST_CASE("AssetValue creates primitive values", "[AssetValue]") {

  SECTION("Number") {
    const Engine::AssetValue value = Engine::AssetValue::makeNumber(42.5);

    REQUIRE(value.isNumber());
    REQUIRE(value.number == 42.5);
    REQUIRE_FALSE(value.isString());
    REQUIRE_FALSE(value.isBoolean());
  }

  SECTION("Boolean") {
    const Engine::AssetValue value = Engine::AssetValue::makeBoolean(true);

    REQUIRE(value.isBoolean());
    REQUIRE(value.boolean);
    REQUIRE_FALSE(value.isNumber());
  }

  SECTION("String") {
    const Engine::AssetValue value = Engine::AssetValue::makeString("car");

    REQUIRE(value.isString());
    REQUIRE(value.string == "car");
  }
}

TEST_CASE("AssetValue creates arrays", "[AssetValue]") {

  Engine::AssetValue::Array values;

  values.push_back(Engine::AssetValue::makeNumber(1));
  values.push_back(Engine::AssetValue::makeNumber(2));
  values.push_back(Engine::AssetValue::makeNumber(3));

  const Engine::AssetValue array =
      Engine::AssetValue::makeArray(std::move(values));

  REQUIRE(array.isArray());
  REQUIRE(array.array.size() == 3);

  REQUIRE(array.array[0].number == 1);
  REQUIRE(array.array[1].number == 2);
  REQUIRE(array.array[2].number == 3);
}

TEST_CASE("AssetValue creates objects", "[AssetValue]") {

  Engine::AssetValue::Object object;

  object["mass"] = Engine::AssetValue::makeNumber(1200);

  object["name"] = Engine::AssetValue::makeString("car");

  const Engine::AssetValue value =
      Engine::AssetValue::makeObject(std::move(object));

  REQUIRE(value.isObject());

  REQUIRE(value.get("mass").isNumber());
  REQUIRE(value.get("mass").number == 1200);

  REQUIRE(value.get("name").isString());
  REQUIRE(value.get("name").string == "car");
}

TEST_CASE("AssetValue throws when accessing missing key", "[AssetValue]") {

  Engine::AssetValue::Object object;

  object["mass"] = Engine::AssetValue::makeNumber(1200);

  const Engine::AssetValue value =
      Engine::AssetValue::makeObject(std::move(object));

  REQUIRE_THROWS(value.get("friction"));
}
