#pragma once

#include <engine/window/WindowAPI.hpp>

namespace Engine {

class OpenGLWindowAPI : public WindowAPI {
public:
  void init() override;

  GLFWwindow *createWindow(const WindowConfig &config) override;

  void destroyWindow(GLFWwindow *window) override;

  void pollEvents() override;

  bool shouldClose(GLFWwindow *window) const override;

  void swapBuffers(GLFWwindow *window) override;

  void makeContextCurrent(GLFWwindow *window) override;
};

} // namespace Engine
