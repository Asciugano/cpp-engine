#pragma once

#include <engine/EngineConfig.hpp>
#include <engine/events/Event.hpp>

#include <functional>

struct GLFWwindow;

namespace Engine {

class Window {
public:
  using EventCallbackFn = std::function<void(Event &)>;

  explicit Window(const WindowConfig &config);

  Window(unsigned int width, unsigned int height, const char *title,
         const GraphicsAPI *api = nullptr);

  ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  Window(Window &&) = delete;
  Window &operator=(Window &&) = delete;

  void setEventCallback(const EventCallbackFn &callback);

  bool shouldClose() const;

  void pollEvents() const;

  void swapBuffers() const;

  GLFWwindow *native() const;

  uint32_t width() const;
  uint32_t height() const;

private:
  void init();

private:
  GLFWwindow *m_window = nullptr;

  unsigned int m_width = 0;
  unsigned int m_height = 0;

  const char *m_title = nullptr;

  GraphicsAPI m_graphycsAPI = GraphicsAPI::OpenGL;

  EventCallbackFn m_eventCallback;
};

} // namespace Engine
