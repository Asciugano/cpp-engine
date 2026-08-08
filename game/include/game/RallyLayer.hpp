#pragma once

#include "engine/events/Event.hpp"
#include <engine/layer/Layer.hpp>

class RallyLayer : public Engine::Layer {
public:
  RallyLayer();

  void onAttach() override;
  void onDetach() override;

  void onUpdate(float dt) override;
  void onEvent(Engine::Event &event) override;

  void onRender() override;

private:
  float m_rotation = 0.0f;
};
