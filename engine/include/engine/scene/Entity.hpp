#pragma once

#include <engine/renderer/Material.hpp>
#include <engine/renderer/Mesh.hpp>
#include <engine/scene/Transform.hpp>
#include <memory>

namespace Engine {
class Entity {
public:
  Entity() = default;
  ~Entity() = default;

  Entity(const Entity &) = delete;
  Entity &operator=(const Entity &) = delete;

  Entity(Entity &&) noexcept = default;
  Entity &operator=(Entity &&) noexcept = default;

  Transform &getTransform();
  const Transform &getTransform() const;

  void setMesh(std::shared_ptr<Mesh> mesh);
  void setMaterial(std::shared_ptr<Material> material);

  Mesh *getMesh();
  const Mesh *getMesh() const;

  Material *getMaterial();
  const Material *getMaterial() const;

  const bool isRendendable() const;

private:
  Transform m_transform;

  std::shared_ptr<Mesh> m_mesh;
  std::shared_ptr<Material> m_material;
};
} // namespace Engine
