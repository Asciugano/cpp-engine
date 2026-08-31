#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
namespace Engine {
class Transform {
public:
  Transform() = default;

  explicit Transform(const glm::vec3 &position);

  Transform(const glm::vec3 &position, const glm::vec3 &rotation,
            const glm::vec3 scale);

  void setPosition(const glm::vec3 &position);
  void setRotation(const glm::vec3 &rotation);
  void setScale(const glm::vec3 &scale);

  void translate(const glm::vec3 &translation);
  void rotate(const glm::vec3 &rotation);
  void scale(const glm::vec3 &scale);

  const glm::vec3 &getPosition() const;
  const glm::vec3 &getRotation() const;
  const glm::vec3 &getScale() const;

  glm::mat4 getMatrix() const;

private:
  glm::vec3 m_position{0.0f};
  glm::vec3 m_rotation{0.0f};
  glm::vec3 m_scale{1.0f};
};
} // namespace Engine
