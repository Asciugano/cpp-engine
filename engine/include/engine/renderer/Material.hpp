#pragma once

#include <engine/renderer/Shader.hpp>
#include <glm/ext/vector_float4.hpp>
#include <memory>

namespace Engine {
class Material {
public:
  explicit Material(std::unique_ptr<Shader> shader);
  Material(std::unique_ptr<Shader> shader, const glm::vec4 &color);

  Shader &getShader();
  const Shader &getShader() const;

  void setColor(const glm::vec4 &color);
  const glm::vec4 &getColor() const;

private:
  std::unique_ptr<Shader> m_shader;
  glm::vec4 m_color{1.0f};
};
} // namespace Engine
