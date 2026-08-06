#pragma once

struct GLFWwindow;

namespace Engine {
class GraphicsContext {
public:
  explicit GraphicsContext(GLFWwindow *window);

  void init();
  void swapBuffers() const;

private:
  GLFWwindow *m_window{};
};
} // namespace Engine
