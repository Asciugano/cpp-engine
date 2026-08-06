#pragma once

namespace Engine {
class Layer {
public:
  Layer(const char *name = "Layer") : m_name(name) {}

  virtual ~Layer() = default;

  virtual void onAttach() = 0;
  virtual void onDetach() = 0;
  virtual void onUpdate(float dt) = 0;
  virtual void onRender() = 0;

protected:
  const char *m_name;
};
} // namespace Engine
