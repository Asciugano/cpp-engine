#pragma once

#include <engine/Key.hpp>

struct GLFWwindow;

namespace Engine {

class Input {
public:
  static void init(GLFWwindow *window);
  static bool isKeyPressed(Key key);

private:
  static GLFWwindow *s_window;
};

} // namespace Engine
