#pragma once

namespace Engine {

class Renderer {
public:
  static void init();

  static void beginFrame();
  static void endFrame();

  static void clear();

  static void setClearColor(float r, float g, float b, float a);
};

} // namespace Engine
