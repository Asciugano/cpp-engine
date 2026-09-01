#include <engine/renderer/Material.hpp>
#include <engine/renderer/Shader.hpp>
#include <glm/ext/vector_float4.hpp>
#include <memory>

namespace Engine {
Material::Material(std::unique_ptr<Shader> shader)
    : m_shader(std::move(shader)) {}

Material::Material(std::unique_ptr<Shader> shader, const glm::vec4 &color)
    : m_shader(std::move(shader)), m_color(color) {}

Shader &Material::getShader() { return *m_shader; }

const Shader &Material::getShader() const { return *m_shader; }

void Material::setColor(const glm::vec4 &color) { m_color = color; }

const glm::vec4 &Material::getColor() const { return m_color; }
} // namespace Engine
