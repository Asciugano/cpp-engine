#pragma once

#include "engine/EngineConfig.hpp"
#include "engine/events/Event.hpp"
#include <memory>

namespace Engine {
class Window;
class GraphicsContext;

class Application {
public:
  explicit Application(const EngineConfig &config);
  ~Application();

  void run();

  void onEvent(Event &event);

private:
  std::unique_ptr<Window> m_window;
  std::unique_ptr<GraphicsContext> m_context;
  bool m_running{true};
  EngineConfig m_config;
};
} // namespace Engine
