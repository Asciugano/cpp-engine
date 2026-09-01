#pragma once

#include "engine/EngineConfig.hpp"
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
  std::unique_ptr<Engine::VertexArray> m_vao;
  std::shared_ptr<Engine::VertexBuffer> m_vbo;
  std::shared_ptr<Engine::IndexBuffer> m_ibo;
  std::unique_ptr<Engine::Shader> m_shader;

  Engine::Transform m_transform;
  Engine::Camera m_camera;

  bool m_initialized = false;
};
