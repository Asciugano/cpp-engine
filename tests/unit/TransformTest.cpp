#include <catch2/catch_test_macros.hpp>

#include <engine/scene/Transform.hpp>

#include <glm/glm.hpp>

TEST_CASE("Transform has correct default values", "[Transform]") {
  Engine::Transform transform;

  REQUIRE(transform.getPosition() == glm::vec3(0.0f));
  REQUIRE(transform.getRotation() == glm::vec3(0.0f));
  REQUIRE(transform.getScale() == glm::vec3(1.0f));
}

TEST_CASE("Transform constructor sets position", "[Transform]") {
  Engine::Transform transform(glm::vec3(1.0f, 2.0f, 3.0f));

  REQUIRE(transform.getPosition() == glm::vec3(1.0f, 2.0f, 3.0f));

  REQUIRE(transform.getRotation() == glm::vec3(0.0f));

  REQUIRE(transform.getScale() == glm::vec3(1.0f));
}

TEST_CASE("Transform setters work", "[Transform]") {
  Engine::Transform transform;

  transform.setPosition({1.0f, 2.0f, 3.0f});
  transform.setRotation({10.0f, 20.0f, 30.0f});
  transform.setScale({2.0f, 3.0f, 4.0f});

  REQUIRE(transform.getPosition() == glm::vec3(1.0f, 2.0f, 3.0f));

  REQUIRE(transform.getRotation() == glm::vec3(10.0f, 20.0f, 30.0f));

  REQUIRE(transform.getScale() == glm::vec3(2.0f, 3.0f, 4.0f));
}

TEST_CASE("Transform translate works", "[Transform]") {
  Engine::Transform transform;

  transform.translate({1.0f, 2.0f, 3.0f});

  REQUIRE(transform.getPosition() == glm::vec3(1.0f, 2.0f, 3.0f));

  transform.translate({2.0f, -1.0f, 4.0f});

  REQUIRE(transform.getPosition() == glm::vec3(3.0f, 1.0f, 7.0f));
}

TEST_CASE("Transform rotate works", "[Transform]") {
  Engine::Transform transform;

  transform.rotate({10.0f, 20.0f, 30.0f});

  REQUIRE(transform.getRotation() == glm::vec3(10.0f, 20.0f, 30.0f));

  transform.rotate({5.0f, -10.0f, 15.0f});

  REQUIRE(transform.getRotation() == glm::vec3(15.0f, 10.0f, 45.0f));
}

TEST_CASE("Transform scale works", "[Transform]") {
  Engine::Transform transform;

  transform.scale({2.0f, 3.0f, 4.0f});

  REQUIRE(transform.getScale() == glm::vec3(2.0f, 3.0f, 4.0f));
}

TEST_CASE("Transform creates identity matrix by default", "[Transform]") {
  Engine::Transform transform;

  glm::mat4 matrix = transform.getMatrix();

  REQUIRE(matrix == glm::mat4(1.0f));
}

TEST_CASE("Transform matrix contains translation", "[Transform]") {
  Engine::Transform transform;

  transform.setPosition({1.0f, 2.0f, 3.0f});

  glm::mat4 matrix = transform.getMatrix();

  REQUIRE(matrix[3][0] == 1.0f);
  REQUIRE(matrix[3][1] == 2.0f);
  REQUIRE(matrix[3][2] == 3.0f);
}

TEST_CASE("Transform matrix contains scale", "[Transform]") {
  Engine::Transform transform;

  transform.setScale({2.0f, 3.0f, 4.0f});

  glm::mat4 matrix = transform.getMatrix();

  REQUIRE(matrix[0][0] == 2.0f);
  REQUIRE(matrix[1][1] == 3.0f);
  REQUIRE(matrix[2][2] == 4.0f);
}
