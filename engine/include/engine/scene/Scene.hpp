#pragma once

#include <engine/scene/Entity.hpp>
#include <memory>
#include <vector>

namespace Engine {
class Scene {
public:
  Scene() = default;
  ~Scene() = default;

  Scene(const Scene &) = delete;
  Scene &operator=(const Scene &) = delete;

  Scene(Scene &&) noexcept = default;
  Scene &operator=(Scene &&) noexcept = default;

  Entity &createEntity();
  void addEntity(std::unique_ptr<Entity> entity);
  void destroyEntity(Entity &entity);
  void cleanScene();

  std::vector<std::unique_ptr<Entity>> &getEntities();
  const std::vector<std::unique_ptr<Entity>> &getEntities() const;

private:
  std::vector<std::unique_ptr<Entity>> m_entities;
};
} // namespace Engine
