#include <engine/EngineConfig.hpp>
#include <engine/platform/OpenGL/OpenGLRendererAPI.hpp>
#include <engine/renderer/Material.hpp>
#include <engine/renderer/RenderComand.hpp>
#include <engine/renderer/Renderer.hpp>
#include <engine/renderer/RendererAPI.hpp>
#include <engine/scene/Transform.hpp>
#include <glbinding/gl/gl.h>

using namespace gl;

namespace Engine {

void Renderer::init(const RendererConfig &config) {
  RendererAPI::setGraphicsAPIs(config.api);

  RenderComand::init();
}

void Renderer::beginFrame() { RenderComand::clear(); }

void Renderer::endFrame() {}

void Renderer::setClearColor(float r, float g, float b, float a) {
  RenderComand::setClearColor(r, g, b, a);
}

void Renderer::draw(Entity &entity, const Camera &camera) {
  entity.getMaterial()->setUniform<glm::vec4>("u_Color",
                                              entity.getMaterial()->getColor());
  entity.getMaterial()->setUniform<glm::mat4>(
      "u_Model", entity.getTransform().getMatrix());
  entity.getMaterial()->setUniform<glm::mat4>("u_View", camera.getViewMatrix());
  entity.getMaterial()->setUniform<glm::mat4>("u_Projection",
                                              camera.getProjectionMatrix());

  RenderComand::drawIndexed(entity.getMesh()->getVertexArray(),
                            entity.getMaterial()->getShader());
}
void Renderer::draw(const Mesh &mesh, Material &material,
                    const Transform &transform, const Camera &camera) {

  material.setUniform<glm::vec4>("u_Color", material.getColor());
  material.setUniform<glm::mat4>("u_Model", transform.getMatrix());
  material.setUniform<glm::mat4>("u_View", camera.getViewMatrix());
  material.setUniform<glm::mat4>("u_Projection", camera.getProjectionMatrix());

  RenderComand::drawIndexed(mesh.getVertexArray(), material.getShader());
}

void Renderer::setViewport(uint32_t x, uint32_t y, uint32_t width,
                           uint32_t height) {
  RenderComand::setViewport(x, y, width, height);
}
} // namespace Engine
