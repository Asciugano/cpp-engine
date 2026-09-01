#include <engine/events/Event.hpp>
#include <engine/renderer/RenderComand.hpp>
#include <engine/renderer/Renderer.hpp>
#include <game/RallyLayer.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <iostream>

RallyLayer::RallyLayer() : Layer("Rally") {}

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

  m_vao = Engine::VertexArray::create();

  m_vbo = std::shared_ptr<Engine::VertexBuffer>(
      Engine::VertexBuffer::create(vertices, sizeof(vertices)).release());

  m_vbo->setLayout({{Engine::ShaderDataType::Float3, "a_Position"}});

  m_vao->addVertexBuffer(m_vbo);

  const uint32_t indexCount = static_cast<uint32_t>(std::size(indices));

  m_ibo = std::shared_ptr<Engine::IndexBuffer>(
      Engine::IndexBuffer::create(indices, indexCount).release());

  m_vao->setIndexBuffer(m_ibo);

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
  std::cout << event.name() << std::endl;
}

void RallyLayer::onRender() {
  if (!m_initialized) {
    onAttach();
  }

  m_shader->bind();

  m_shader->setMat4("u_Model", m_transform.getMatrix());
  m_shader->setMat4("u_View", m_camera.getViewMatrix());
  m_shader->setMat4("u_Projection", m_camera.getProjectionMatrix());

  Engine::Renderer::draw(*m_vao, *m_shader);
}
