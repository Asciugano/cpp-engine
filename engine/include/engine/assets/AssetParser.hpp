#pragma once

#include <engine/assets/AssetData.hpp>
#include <string>

namespace Engine {
class AssetParser {
public:
  static AssetData parse(const std::string &path);

private:
  AssetParser() = delete;
};
} // namespace Engine
