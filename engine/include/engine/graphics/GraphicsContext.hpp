#pragma once

#include <engine/EngineConfig.hpp>

struct GLFWwindow;

namespace Engine {
class GraphicsContext {
public:
  explicit GraphicsContext(GLFWwindow *window);

  void init(const WindowConfig &config);
  void swapBuffers() const;

private:
  GLFWwindow *m_window{};
};
} // namespace Engine
