#pragma once

#include "engine/events/Event.hpp"
namespace Engine {
class Layer {
public:
  Layer(const char *name = "Layer") : m_name(name) {}

  virtual ~Layer() = default;

  virtual void onAttach() = 0;
  virtual void onDetach() {};
  virtual void onUpdate(float dt) {};
  virtual void onRender() = 0;
  virtual void onEvent(Event &event) {};

  const char *name() const { return m_name; }

protected:
  const char *m_name;
};
} // namespace Engine
