#include <cassert>
#include <engine/renderer/Material.hpp>
#include <engine/renderer/Shader.hpp>
#include <glm/vec4.hpp>
#include <memory>

namespace Engine {
Material::Material(std::unique_ptr<Shader> shader)
    : m_shader(std::move(shader)) {

  assert(m_shader && "Material requires a valid Shader");
}

Material::Material(std::unique_ptr<Shader> shader, const glm::vec4 &color)
    : m_shader(std::move(shader)), m_color(color) {

  assert(m_shader && "Material requires a valid Shader");
}

Shader &Material::getShader() { return *m_shader; }

void Material::setColor(const glm::vec4 &color) { m_color = color; }

const glm::vec4 &Material::getColor() const { return m_color; }

void Material::bind(const char *name) const {
  m_shader->bind();
  m_shader->setVec4(name, m_color);
}
} // namespace Engine
