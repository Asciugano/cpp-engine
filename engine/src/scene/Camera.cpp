#include "glm/geometric.hpp"
#include <cmath>
#include <engine/scene/Camera.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

namespace Engine {
Camera::Camera(float fov, float aspectRatio, float nearClip, float farClip)
    : m_fov(fov), m_aspectRatio(aspectRatio), m_nearClip(nearClip),
      m_farClip(farClip) {

  updateViewMatrix();
  updateProjectionMatrix();
}

void Camera::setPosition(const glm::vec3 &position) {
  m_position = position;

  updateViewMatrix();
}

void Camera::setRotation(const glm::vec3 &rotation) {
  m_rotation = rotation;

  updateViewMatrix();
}

void Camera::setFov(float fov) {
  m_fov = fov;

  updateProjectionMatrix();
}

void Camera::setAspectRatio(float aspectRatio) {
  if (aspectRatio <= 0)
    return;

  m_aspectRatio = aspectRatio;

  updateProjectionMatrix();
}

void Camera::setNearClip(float nearClip) {
  m_nearClip = nearClip;

  updateProjectionMatrix();
}

void Camera::setFarClip(float farClip) {
  m_farClip = farClip;

  updateProjectionMatrix();
}

const glm::vec3 &Camera::getPosition() const { return m_position; }

const glm::vec3 &Camera::getRotation() const { return m_rotation; }

float Camera::getFov() const { return m_fov; }

float Camera::getAspectRatio() const { return m_aspectRatio; }

float Camera::getNearClip() const { return m_nearClip; }

float Camera::getFarClip() const { return m_farClip; }

const glm::mat4 &Camera::getViewMatrix() const { return m_viewMatrix; }

const glm::mat4 &Camera::getProjectionMatrix() const {
  return m_projectionMatrix;
}

void Camera::updateViewMatrix() {
  glm::mat4 rotation{1.0f};

  rotation = glm::rotate(rotation, glm::radians(m_rotation.x),
                         glm::vec3(1.0f, 0.0f, 0.0f));

  rotation = glm::rotate(rotation, glm::radians(m_rotation.y),
                         glm::vec3(0.0f, 1.0f, 0.0f));

  rotation = glm::rotate(rotation, glm::radians(m_rotation.z),
                         glm::vec3(0.0f, 0.0f, 1.0f));

  glm::vec3 forward = glm::vec3(rotation * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));

  glm::vec3 up = glm::vec3(rotation * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

  m_viewMatrix = glm::lookAt(m_position, m_position + forward, up);
}

void Camera::updateProjectionMatrix() {
  m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio,
                                        m_nearClip, m_farClip);
}

void Camera::lookAt(const glm::vec3 &target) {
  glm::vec3 direction = glm::normalize(target - m_position);

  m_rotation.y = glm::degrees(std::atan2(direction.x, -direction.z));
  m_rotation.x = glm::degrees(std::asin(-direction.y));

  m_rotation.z = 0.0f;

  updateViewMatrix();
}
} // namespace Engine
