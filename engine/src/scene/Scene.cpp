#include <algorithm>
#include <engine/scene/Scene.hpp>
#include <memory>
#include <stdexcept>

namespace Engine {
Entity &Scene::createEntity() {
  auto entity = std::make_unique<Entity>();

  Entity &reference = *entity;

  m_entities.push_back(std::move(entity));
  return reference;
}

void Scene::destroyEntity(Entity &entity) {
  const auto it =
      std::find_if(m_entities.begin(), m_entities.end(),
                   [&entity](const std::unique_ptr<Entity> &current) {
                     return current.get() == &entity;
                   });

  if (it == m_entities.end()) {
    throw std::invalid_argument("Entity does not belong to this scene");
  }

  m_entities.erase(it);
}

std::vector<std::unique_ptr<Entity>> &Scene::getEntities() {
  return m_entities;
}
const std::vector<std::unique_ptr<Entity>> &Scene::getEntities() const {
  return m_entities;
}
} // namespace Engine
