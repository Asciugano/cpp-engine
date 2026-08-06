#pragma once

namespace Engine {
class RendererAPI {
public:
  virtual ~RendererAPI() = default;

  virtual void init() = 0;
  virtual void clear() = 0;

  virtual void setClearColor(float r, float g, float b, float a) = 0;
};
} // namespace Engine
