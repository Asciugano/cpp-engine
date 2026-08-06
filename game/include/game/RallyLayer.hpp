#pragma once

#include <engine/layer/Layer.hpp>

class RallyLayer : public Engine::Layer {
public:
  RallyLayer();

  void onAttach() override;

  void onUpdate(float dt) override;

  void onRender() override;

private:
  float m_rotation = 0.0f;
};
