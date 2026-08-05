#pragma once

#include "engine/Window.hpp"
#include <memory>

namespace Engine {
class Window;

class Application {
public:
  Application();
  Application(const char *title);
  Application(unsigned int width, unsigned int height, const char *title);
  ~Application();

  void run();

private:
  std::unique_ptr<Window> m_window;
  bool m_running{true};
};
} // namespace Engine
