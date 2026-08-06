#pragma once

#include "engine/EngineConfig.hpp"
struct GLFWwindow;

namespace Engine {
class Window {
public:
  Window(unsigned int width, unsigned int height, const char *title);
  Window(const WindowConfig &config);
  ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  Window(Window &&) = delete;
  Window &operator=(Window &&) = delete;

  bool shoudClose() const;
  void pollEvents() const;
  void swapBuffers() const;
  GLFWwindow *native() const;

private:
  GLFWwindow *m_window{};
};

} // namespace Engine
