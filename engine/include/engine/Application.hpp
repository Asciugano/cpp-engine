#pragma once

#include <memory>

namespace Engine {
class Window;
class GraphicsContext;

class Application {
public:
  Application();
  Application(const char *title);
  Application(unsigned int width, unsigned int height, const char *title);
  ~Application();

  void run();

private:
  std::unique_ptr<Window> m_window;
  std::unique_ptr<GraphicsContext> m_context;
  bool m_running{true};
};
} // namespace Engine
