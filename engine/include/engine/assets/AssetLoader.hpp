#pragma once

#include <engine/scene/Entity.hpp>
#include <memory>

namespace Engine {
class AssetLoader {
public:
  static std::unique_ptr<Entity> load(const std::string &path);
  static std::unique_ptr<Entity> load(const std::string &path,
                                      const std::string &vertexPath,
                                      const std::string &fragPath,
                                      const glm::vec4 &color);

private:
  AssetLoader() = delete;
};
} // namespace Engine
