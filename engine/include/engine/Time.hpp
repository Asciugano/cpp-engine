#pragma once

namespace Engine {
class Time {
public:
  static void update();
  static float deltaTime();
  static float elapsed();
  static float fps();

private:
  static float s_deltaTime;
  static float s_elapsedTime;
  static float s_lastFrame;
};
} // namespace Engine
