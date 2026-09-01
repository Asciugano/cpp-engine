#include "engine/renderer/Mesh.hpp"
#include "engine/renderer/ShaderDataType.hpp"
#include <engine/EngineConfig.hpp>
#include <engine/events/ApplicationEvent.hpp>
#include <engine/events/Event.hpp>
#include <engine/events/EventDispacher.hpp>
#include <engine/renderer/RenderComand.hpp>
#include <engine/renderer/Renderer.hpp>
#include <engine/scene/Camera.hpp>
#include <game/RallyLayer.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <iostream>

RallyLayer::RallyLayer(const Engine::WindowConfig &config)
    : Layer("Rally"), m_camera(45.0f,
                               static_cast<float>(config.width) /
                                   static_cast<float>(config.height),
                               0.1f, 100.f) {}

void RallyLayer::onAttach() {
  float vertices[] = {
      // Front
      -0.5f, -0.5f, 0.5f, // 0
      0.5f, -0.5f, 0.5f,  // 1
      0.5f, 0.5f, 0.5f,   // 2
      -0.5f, 0.5f, 0.5f,  // 3

      // Back
      -0.5f, -0.5f, -0.5f, // 4
      0.5f, -0.5f, -0.5f,  // 5
      0.5f, 0.5f, -0.5f,   // 6
      -0.5f, 0.5f, -0.5f   // 7
  };

  uint32_t indices[] = {// Front
                        0, 1, 2, 2, 3, 0,

                        // Back
                        5, 4, 7, 7, 6, 5,

                        // Left
                        4, 0, 3, 3, 7, 4,

                        // Right
                        1, 5, 6, 6, 2, 1,

                        // Top
                        3, 2, 6, 6, 7, 3,

                        // Bottom
                        4, 5, 1, 1, 0, 4};

  m_mesh = Engine::Mesh::create(
      vertices, sizeof(vertices), indices, std::size(indices),
      {{Engine::ShaderDataType::Float3, "a_Position"}});

  m_shader = Engine::Shader::create("assets/shaders/basic.vert",
                                    "assets/shaders/basic.frag");

  m_shader->bind();

  m_shader->setVec4("u_Color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

  m_initialized = true;
}

void RallyLayer::onDetach() { std::cout << "RallyLayer Detached" << std::endl; }

void RallyLayer::onUpdate(float dt) {
  m_transform.rotate(glm::vec3(0.0f, 90.f * dt, 0.0f));
}

void RallyLayer::onEvent(Engine::Event &event) {
  Engine::EventDispacher dispacher(event);

  dispacher.dispatch<Engine::WindowResizeEvent>(
      [this](Engine::WindowResizeEvent &event) {
        if (event.height() == 0)
          return false;

        const float aspectRatio = static_cast<float>(event.width()) /
                                  static_cast<float>(event.height());

        m_camera.setAspectRatio(aspectRatio);

        Engine::Renderer::setViewport(0, 0, event.width(), event.height());

        return false;
      });
}

void RallyLayer::onRender() {
  if (!m_initialized) {
    onAttach();
  }

  m_shader->bind();

  m_shader->setMat4("u_Model", m_transform.getMatrix());
  m_shader->setMat4("u_View", m_camera.getViewMatrix());
  m_shader->setMat4("u_Projection", m_camera.getProjectionMatrix());

  Engine::Renderer::draw(m_mesh->getVertexArray(), *m_shader);
}
