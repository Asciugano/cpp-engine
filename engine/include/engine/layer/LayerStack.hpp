#pragma once

#include <engine/layer/Layer.hpp>
#include <memory>
#include <stdexcept>
#include <vector>

namespace Engine {
class LayerStack {
public:
  void pushLayer(std::shared_ptr<Layer> layer) {
    if (!layer)
      throw std::runtime_error("Trying to push a null Layer.");

    m_layers.push_back(layer);
    layer->onAttach();
  }

  auto begin() { return m_layers.begin(); }

  auto end() { return m_layers.end(); }

private:
  std::vector<std::shared_ptr<Layer>> m_layers{};
};
} // namespace Engine
