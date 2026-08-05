#include <GLFW/glfw3.h>
#include <engine/Time.hpp>

namespace Engine {
float Time::s_deltaTime = 0.0f;
float Time::s_elapsedTime = 0.0f;
float Time::s_lastFrame = 0.0f;

void Time::update() {
  float current = glfwGetTime();
  s_deltaTime = current - s_lastFrame;
  s_lastFrame = current;
  s_elapsedTime = current;
}

float Time::fps() {
  if (s_deltaTime <= 0)
    return 0;

  return 1.0f / s_deltaTime;
}

float Time::deltaTime() { return s_deltaTime; }
float Time::elapsed() { return s_elapsedTime; }
} // namespace Engine
