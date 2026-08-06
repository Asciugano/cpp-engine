#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <engine/inputs/Input.hpp>

namespace Engine {
GLFWwindow *Input::s_window = nullptr;

void Input::setWindow(GLFWwindow *window) { s_window = window; }

bool Input::isKeyPressed(Key key) {
  if (!s_window)
    return false;

  return glfwGetKey(s_window, static_cast<int>(key)) == GLFW_PRESS;
}

} // namespace Engine
