#pragma once

#include <engine/EngineConfig.hpp>
#include <engine/window/WindowAPI.hpp>

#include <memory>

struct GLFWwindow;

namespace Engine {

class WindowCommand {
public:
  static void init(GraphicsAPI api);

  static GLFWwindow *createWindow(const WindowConfig &config);

  static void destroyWindow(GLFWwindow *window);

  static void pollEvents();

  static bool shouldClose(GLFWwindow *window);

  static void swapBuffers(GLFWwindow *window);

  static void makeContextCurrent(GLFWwindow *window);

private:
  static std::unique_ptr<WindowAPI> s_windowAPI;
};

} // namespace Engine
