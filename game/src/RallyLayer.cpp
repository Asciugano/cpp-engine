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
  float vertices[] = {// position
                      0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f};

  uint32_t indices[] = {0, 1, 2};

  m_vao = Engine::VertexArray::create();

  m_vbo = std::shared_ptr<Engine::VertexBuffer>(
      Engine::VertexBuffer::create(vertices, sizeof(vertices)).release());

  m_vbo->setLayout({{Engine::ShaderDataType::Float3, "a_Position"}});

  m_vao->addVertexBuffer(m_vbo);

  m_ibo = std::shared_ptr<Engine::IndexBuffer>(
      Engine::IndexBuffer::create(indices, 3).release());

  m_vao->setIndexBuffer(m_ibo);

  m_shader = Engine::Shader::create("assets/shaders/basic.vert",
                                    "assets/shaders/basic.frag");

  m_shader->bind();

  m_shader->setVec4("u_Color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

  m_initialized = true;
}

void RallyLayer::onDetach() { std::cout << "RallyLayer Detached" << std::endl; }

void RallyLayer::onUpdate(float dt) {}

void RallyLayer::onEvent(Engine::Event &event) {
  std::cout << event.name() << std::endl;
}

void RallyLayer::onRender() {
  if (!m_initialized) {
    onAttach();
  }

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view =
      glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f));

  glm::mat4 projection =
      glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

  m_shader->bind();

  m_shader->setMat4("u_Model", model);
  m_shader->setMat4("u_View", view);
  m_shader->setMat4("u_Projection", projection);

  Engine::Renderer::draw(*m_vao, *m_shader);
}
