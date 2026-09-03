#pragma once

#include <engine/EngineConfig.hpp>
#include <engine/events/Event.hpp>
#include <engine/layer/Layer.hpp>
#include <engine/renderer/Material.hpp>
#include <engine/renderer/Mesh.hpp>
#include <engine/renderer/Shader.hpp>
#include <engine/renderer/VertexArray.hpp>
#include <engine/scene/Camera.hpp>
#include <engine/scene/Entity.hpp>
#include <engine/scene/Transform.hpp>

class RallyLayer : public Engine::Layer {
public:
  RallyLayer(const Engine::WindowConfig &config);

  void onAttach() override;
  void onDetach() override;

  void onUpdate(float dt) override;
  void onEvent(Engine::Event &event) override;

  void onRender() override;

private:
  Engine::Entity car;
  Engine::Camera m_camera;

  bool m_initialized = false;
};
