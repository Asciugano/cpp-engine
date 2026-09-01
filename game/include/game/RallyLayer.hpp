#pragma once

#include "engine/EngineConfig.hpp"
#include "engine/renderer/Mesh.hpp"
#include <engine/events/Event.hpp>
#include <engine/layer/Layer.hpp>
#include <engine/renderer/Shader.hpp>
#include <engine/renderer/VertexArray.hpp>
#include <engine/scene/Camera.hpp>
#include <engine/scene/Transform.hpp>
#include <memory>

class RallyLayer : public Engine::Layer {
public:
  RallyLayer(const Engine::WindowConfig &config);

  void onAttach() override;
  void onDetach() override;

  void onUpdate(float dt) override;
  void onEvent(Engine::Event &event) override;

  void onRender() override;

private:
  std::unique_ptr<Engine::Mesh> m_mesh;
  std::unique_ptr<Engine::Shader> m_shader;

  Engine::Transform m_transform;
  Engine::Camera m_camera;

  bool m_initialized = false;
};
