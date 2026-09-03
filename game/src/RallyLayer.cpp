#include <engine/EngineConfig.hpp>
#include <engine/assets/AssetLoader.hpp>
#include <engine/events/ApplicationEvent.hpp>
#include <engine/events/Event.hpp>
#include <engine/events/EventDispacher.hpp>
#include <engine/renderer/Material.hpp>
#include <engine/renderer/Mesh.hpp>
#include <engine/renderer/RenderComand.hpp>
#include <engine/renderer/Renderer.hpp>
#include <engine/renderer/Shader.hpp>
#include <engine/renderer/ShaderDataType.hpp>
#include <engine/scene/Camera.hpp>
#include <game/RallyLayer.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <memory>

RallyLayer::RallyLayer(const Engine::WindowConfig &config)
    : Layer("Rally"), m_camera(45.0f,
                               static_cast<float>(config.width) /
                                   static_cast<float>(config.height),
                               0.1f, 100.f) {}

void RallyLayer::onAttach() {
  auto entity = Engine::AssetLoader::load(
      "assets/models/cube.cba", "assets/shaders/basic.vert",
      "assets/shaders/basic.frag", glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

  m_car = entity.get();
  m_scene.addEntity(std::move(entity));
  m_initialized = true;
}

void RallyLayer::onDetach() {
  std::cout << "RallyLayer Detached" << std::endl;
  m_scene.cleanScene();
}

void RallyLayer::onUpdate(float dt) {
  m_car->getTransform().rotate(glm::vec3(15.0f * dt, 90.f * dt, 15.0f * dt));
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

  Engine::Renderer::draw(m_scene, m_camera);
}
