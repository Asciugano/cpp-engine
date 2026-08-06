#pragma once

#include <engine/inputs/KeyCodes.hpp>

struct GLFWwindow;

namespace Engine {

class Input {
public:
  static bool isKeyPressed(Key key);

  static void setWindow(GLFWwindow *window);

private:
  static GLFWwindow *s_window;
};

} // namespace Engine
