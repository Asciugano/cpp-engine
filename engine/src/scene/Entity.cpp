#include "engine/renderer/Material.hpp"
#include <engine/scene/Entity.hpp>
#include <engine/scene/Transform.hpp>
#include <memory>

namespace Engine {
Transform &Entity::getTransform() { return m_transform; }
const Transform &Entity::getTransform() const { return m_transform; }

Mesh *Entity::getMesh() { return m_mesh.get(); }
const Mesh *Entity::getMesh() const { return m_mesh.get(); }

Material *Entity::getMaterial() { return m_material.get(); }
const Material *Entity::getMaterial() const { return m_material.get(); }

void Entity::setMesh(std::shared_ptr<Mesh> mesh) { m_mesh = mesh; }

void Entity::setMaterial(std::shared_ptr<Material> material) {
  m_material = material;
}
} // namespace Engine
