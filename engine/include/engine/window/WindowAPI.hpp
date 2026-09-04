#pragma once

#include <engine/EngineConfig.hpp>

struct GLFWwindow;

namespace Engine {

class WindowAPI {
public:
  virtual ~WindowAPI() = default;

  virtual void init() = 0;

  virtual GLFWwindow *createWindow(const WindowConfig &config) = 0;

  virtual void destroyWindow(GLFWwindow *window) = 0;

  virtual void pollEvents() = 0;

  virtual bool shouldClose(GLFWwindow *window) const = 0;

  virtual void swapBuffers(GLFWwindow *window) = 0;

  virtual void makeContextCurrent(GLFWwindow *window) = 0;

  static std::unique_ptr<WindowAPI> create(GraphicsAPI api);
};

} // namespace Engine
