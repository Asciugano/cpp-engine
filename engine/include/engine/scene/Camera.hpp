#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

namespace Engine {
class Camera {
public:
  Camera(float fov, float aspectRatio, float nearClip, float farClip);

  void setPosition(const glm::vec3 &position);
  void setRotation(const glm::vec3 &rotation);

  void setFov(float fov);
  void setAspectRatio(float aspectRatio);
  void setNearClip(float nearClip);
  void setFarClip(float farClip);

  const glm::vec3 &getPosition() const;
  const glm::vec3 &getRotation() const;

  float getFov() const;
  float getAspectRatio() const;
  float getNearClip() const;
  float getFarClip() const;

  const glm::mat4 &getViewMatrix() const;
  const glm::mat4 &getProjectionMatrix() const;

  void lookAt(const glm::vec3 &target);

private:
  void updateViewMatrix();
  void updateProjectionMatrix();

private:
  glm::vec3 m_position{0.0f, 0.0f, 3.0f};
  glm::vec3 m_rotation{0.0f};

  float m_fov{45.0f};
  float m_aspectRatio{16.0f / 9.0f};
  float m_nearClip{0.1f};
  float m_farClip{100.0f};

  glm::mat4 m_viewMatrix{1.0f};
  glm::mat4 m_projectionMatrix{1.0f};
};
} // namespace Engine
