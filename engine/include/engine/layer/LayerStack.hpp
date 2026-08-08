#pragma once

#include <engine/layer/Layer.hpp>
#include <memory>
#include <vector>

namespace Engine {
class LayerStack {
public:
  using LayerPtr = std::shared_ptr<Layer>;
  using Container = std::vector<LayerPtr>;

public:
  LayerStack() = default;
  ~LayerStack();

  void pushLayer(LayerPtr layer);
  void pushOverlay(LayerPtr overlay);

  void popLayer(LayerPtr layer);
  void popOverlay(LayerPtr overlay);

  Container::iterator begin() { return m_layers.begin(); }

  Container::iterator end() { return m_layers.end(); }

  Container::const_iterator begin() const { return m_layers.begin(); }

  Container::const_iterator end() const { return m_layers.end(); }

  std::size_t size() const { return m_layers.size(); }

private:
  Container m_layers{};
  std::size_t m_layerInsertIndex = 0;
};
} // namespace Engine
