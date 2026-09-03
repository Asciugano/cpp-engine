#pragma once

#include <engine/EngineConfig.hpp>
#include <engine/renderer/Material.hpp>
#include <engine/renderer/Mesh.hpp>
#include <engine/scene/Camera.hpp>
#include <engine/scene/Entity.hpp>
#include <engine/scene/Scene.hpp>
#include <engine/scene/Transform.hpp>

namespace Engine {

class RendererAPI;

class Renderer {
public:
  static void init(const RendererConfig &config);

  static void beginFrame();
  static void endFrame();

  static void setClearColor(float r, float g, float b, float a);

  static void draw(Scene &scene, const Camera &camera);
  static void draw(Entity &entity, const Camera &camera);
  static void draw(const Mesh &mesh, Material &material,
                   const Transform &transform, const Camera &camera);

  static void setViewport(uint32_t x, uint32_t y, uint32_t width,
                          uint32_t height);
};

} // namespace Engine
