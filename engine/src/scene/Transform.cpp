#include <engine/scene/Transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>

namespace Engine {
Transform::Transform(const glm::vec3 &position) : m_position(position) {}

Transform::Transform(const glm::vec3 &position, const glm::vec3 &rotation,
                     const glm::vec3 scale)
    : m_position(position), m_rotation(rotation), m_scale(scale) {}

void Transform::setPosition(const glm::vec3 &position) {
  m_position = position;
}
void Transform::setRotation(const glm::vec3 &rotation) {
  m_rotation = rotation;
}
void Transform::setScale(const glm::vec3 &scale) { m_scale = scale; }

const glm::vec3 &Transform::getPosition() const { return m_position; }
const glm::vec3 &Transform::getRotation() const { return m_rotation; }
const glm::vec3 &Transform::getScale() const { return m_scale; }

glm::mat4 Transform::getMatrix() const {
  glm::mat4 matrix(1.0f);

  matrix = glm::translate(matrix, m_position);
  matrix = glm::rotate(matrix, glm::radians(m_rotation.x),
                       glm::vec3(1.0f, 0.0f, 0.0f));
  matrix = glm::rotate(matrix, glm::radians(m_rotation.y),
                       glm::vec3(0.0f, 1.0f, 0.0f));
  matrix = glm::rotate(matrix, glm::radians(m_rotation.z),
                       glm::vec3(0.0f, 0.0f, 1.0f));
  matrix = glm::scale(matrix, m_scale);

  return matrix;
}

void Transform::translate(const glm::vec3 &translation) {
  m_position += translation;
}
void Transform::rotate(const glm::vec3 &rotation) { m_rotation += rotation; }
void Transform::scale(const glm::vec3 &scale) { m_scale *= scale; }
} // namespace Engine
