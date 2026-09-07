#include <catch2/catch_test_macros.hpp>

#include <engine/window/Window.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

struct WindowFixture {
  WindowFixture() { glfwInit(); }
  ~WindowFixture() { glfwTerminate(); }
};

TEST_CASE_METHOD(WindowFixture, "Window creates successfully", "[Window]") {
  Engine::WindowConfig config;

  config.title = "Window Test";
  config.width = 800;
  config.height = 600;
  config.api = Engine::GraphicsAPI::OpenGL;

  Engine::Window window(config);

  REQUIRE(window.native() != nullptr);
}

TEST_CASE_METHOD(WindowFixture, "Window has correct dimensions", "[Window]") {
  Engine::WindowConfig config;

  config.title = "Window Size Test";
  config.width = 1280;
  config.height = 720;
  config.api = Engine::GraphicsAPI::OpenGL;

  Engine::Window window(config);

  REQUIRE(window.width() == 1280);
  REQUIRE(window.height() == 720);
}

TEST_CASE_METHOD(WindowFixture, "Window is not initially marked for closing",
                 "[Window]") {
  Engine::WindowConfig config;

  config.title = "Window Close Test";
  config.width = 800;
  config.height = 600;
  config.api = Engine::GraphicsAPI::OpenGL;

  Engine::Window window(config);

  REQUIRE_FALSE(window.shouldClose());
}

TEST_CASE_METHOD(WindowFixture, "Window can be marked for closing",
                 "[Window]") {
  Engine::WindowConfig config;

  config.title = "Window Close Test";
  config.width = 800;
  config.height = 600;
  config.api = Engine::GraphicsAPI::OpenGL;

  Engine::Window window(config);

  REQUIRE_FALSE(window.shouldClose());

  glfwSetWindowShouldClose(window.native(), GLFW_TRUE);

  REQUIRE(window.shouldClose());
}

TEST_CASE_METHOD(WindowFixture, "Window processes events", "[Window]") {
  Engine::WindowConfig config;

  config.title = "Window Events Test";
  config.width = 800;
  config.height = 600;
  config.api = Engine::GraphicsAPI::OpenGL;

  Engine::Window window(config);

  REQUIRE_NOTHROW(window.pollEvents());
}
