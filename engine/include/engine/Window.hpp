#pragma once

#include <cstdint>
#include <engine/EngineConfig.hpp>
#include <engine/events/Event.hpp>
#include <functional>

struct GLFWwindow;

namespace Engine {
using EventCallbackFn = std::function<void(Event &)>;

class Window {
public:
  Window(unsigned int width, unsigned int height, const char *title);
  Window(const WindowConfig &config);
  ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  Window(Window &&) = delete;
  Window &operator=(Window &&) = delete;

  void onUpdate();

  bool shoudClose() const;
  void pollEvents() const;
  void swapBuffers() const;
  GLFWwindow *native() const;

  uint32_t width() const;
  uint32_t height() const;

  void setEventCallback(const EventCallbackFn &callback);

private:
  void init();

  GLFWwindow *m_window{};

  uint32_t m_width;
  uint32_t m_height;

  const char *m_title;

  EventCallbackFn m_eventCallback;
};

} // namespace Engine
