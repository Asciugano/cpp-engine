#include <catch2/catch_test_macros.hpp>

#include <engine/renderer/ShaderDataType.hpp>

TEST_CASE("ShaderDataType float sizes", "[ShaderDataType]") {
  REQUIRE(Engine::shaderDataTypeSize(Engine::ShaderDataType::Float) ==
          sizeof(float));

  REQUIRE(Engine::shaderDataTypeSize(Engine::ShaderDataType::Float2) ==
          2 * sizeof(float));

  REQUIRE(Engine::shaderDataTypeSize(Engine::ShaderDataType::Float3) ==
          3 * sizeof(float));

  REQUIRE(Engine::shaderDataTypeSize(Engine::ShaderDataType::Float4) ==
          4 * sizeof(float));
}

TEST_CASE("ShaderDataType matrix sizes", "[ShaderDataType]") {
  REQUIRE(Engine::shaderDataTypeSize(Engine::ShaderDataType::Mat3) ==
          9 * sizeof(float));

  REQUIRE(Engine::shaderDataTypeSize(Engine::ShaderDataType::Mat4) ==
          16 * sizeof(float));
}

TEST_CASE("ShaderDataType integer sizes", "[ShaderDataType]") {
  REQUIRE(Engine::shaderDataTypeSize(Engine::ShaderDataType::Int) ==
          sizeof(int));

  REQUIRE(Engine::shaderDataTypeSize(Engine::ShaderDataType::Int2) ==
          2 * sizeof(int));

  REQUIRE(Engine::shaderDataTypeSize(Engine::ShaderDataType::Int3) ==
          3 * sizeof(int));

  REQUIRE(Engine::shaderDataTypeSize(Engine::ShaderDataType::Int4) ==
          4 * sizeof(int));
}

TEST_CASE("ShaderDataType bool size", "[ShaderDataType]") {
  REQUIRE(Engine::shaderDataTypeSize(Engine::ShaderDataType::Bool) ==
          sizeof(bool));
}

TEST_CASE("ShaderDataType component counts", "[ShaderDataType]") {
  REQUIRE(Engine::shaderDataTypeComponentCount(Engine::ShaderDataType::Float) ==
          1);

  REQUIRE(Engine::shaderDataTypeComponentCount(
              Engine::ShaderDataType::Float2) == 2);

  REQUIRE(Engine::shaderDataTypeComponentCount(
              Engine::ShaderDataType::Float3) == 3);

  REQUIRE(Engine::shaderDataTypeComponentCount(
              Engine::ShaderDataType::Float4) == 4);

  REQUIRE(Engine::shaderDataTypeComponentCount(Engine::ShaderDataType::Mat3) ==
          9);

  REQUIRE(Engine::shaderDataTypeComponentCount(Engine::ShaderDataType::Mat4) ==
          16);

  REQUIRE(Engine::shaderDataTypeComponentCount(Engine::ShaderDataType::Int) ==
          1);

  REQUIRE(Engine::shaderDataTypeComponentCount(Engine::ShaderDataType::Int2) ==
          2);

  REQUIRE(Engine::shaderDataTypeComponentCount(Engine::ShaderDataType::Int3) ==
          3);

  REQUIRE(Engine::shaderDataTypeComponentCount(Engine::ShaderDataType::Int4) ==
          4);

  REQUIRE(Engine::shaderDataTypeComponentCount(Engine::ShaderDataType::Bool) ==
          1);
}
