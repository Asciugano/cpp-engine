#include <catch2/catch_test_macros.hpp>

#include <engine/renderer/BufferLayout.hpp>
#include <engine/renderer/ShaderDataType.hpp>

TEST_CASE("BufferLayout calculates stride", "[BufferLayout]") {
  Engine::BufferLayout layout = {
      {Engine::ShaderDataType::Float3, "a_Position"},
      {Engine::ShaderDataType::Float3, "a_Normal"},
      {Engine::ShaderDataType::Float2, "a_TexCoord"}};

  REQUIRE(layout.getStride() == 8 * sizeof(float));
}

TEST_CASE("BufferLayout calculates offsets", "[BufferLayout]") {
  Engine::BufferLayout layout = {
      {Engine::ShaderDataType::Float3, "a_Position"},
      {Engine::ShaderDataType::Float3, "a_Normal"},
      {Engine::ShaderDataType::Float2, "a_TexCoord"}};

  const auto &elements = layout.getElements();

  REQUIRE(elements.size() == 3);

  REQUIRE(elements[0].offset == 0);
  REQUIRE(elements[1].offset == 3 * sizeof(float));
  REQUIRE(elements[2].offset == 6 * sizeof(float));
}

TEST_CASE("BufferLayout preserves element information", "[BufferLayout]") {
  Engine::BufferLayout layout = {
      {Engine::ShaderDataType::Float3, "a_Position"},
      {Engine::ShaderDataType::Float2, "a_TexCoord"}};

  const auto &elements = layout.getElements();

  REQUIRE(elements[0].name == "a_Position");
  REQUIRE(elements[0].type == Engine::ShaderDataType::Float3);
  REQUIRE(elements[0].size == 3 * sizeof(float));
  REQUIRE(elements[0].getCompenentCount() == 3);

  REQUIRE(elements[1].name == "a_TexCoord");
  REQUIRE(elements[1].type == Engine::ShaderDataType::Float2);
  REQUIRE(elements[1].size == 2 * sizeof(float));
  REQUIRE(elements[1].getCompenentCount() == 2);
}

TEST_CASE("Empty BufferLayout has zero stride", "[BufferLayout]") {
  Engine::BufferLayout layout;

  REQUIRE(layout.getStride() == 0);
  REQUIRE(layout.getElements().empty());
}
