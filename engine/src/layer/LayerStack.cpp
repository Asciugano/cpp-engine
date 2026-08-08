#include <cstddef>
#include <engine/layer/LayerStack.hpp>

#include <algorithm>
#include <stdexcept>

namespace Engine {
LayerStack::~LayerStack() {
  for (auto &layer : m_layers) {
    if (layer)
      layer->onDetach();
  }
}

void LayerStack::pushLayer(LayerPtr layer) {
  if (!layer)
    throw std::runtime_error("Cannot push a null layer");

  m_layers.emplace(m_layers.begin() +
                       static_cast<std::ptrdiff_t>(m_layerInsertIndex),
                   std::move(layer));

  ++m_layerInsertIndex;
  m_layers[m_layerInsertIndex - 1]->onAttach();
}

void LayerStack::pushOverlay(LayerPtr overlay) {
  if (!overlay)
    throw std::runtime_error("Cannot push a null overlay");

  m_layers.emplace_back(std::move(overlay));

  m_layers.back()->onAttach();
}

void LayerStack::popLayer(LayerPtr layer) {
  auto it = std::find(m_layers.begin(),
                      m_layers.begin() +
                          static_cast<std::ptrdiff_t>(m_layerInsertIndex),
                      layer);

  if (it == m_layers.begin() + static_cast<std::ptrdiff_t>(m_layerInsertIndex))
    return;

  (*it)->onDetach();

  m_layers.erase(it);
  --m_layerInsertIndex;
}

void LayerStack::popOverlay(LayerPtr overlay) {
  auto it = std::find(m_layers.begin() +
                          static_cast<std::ptrdiff_t>(m_layerInsertIndex),
                      m_layers.end(), overlay);

  if (it == m_layers.end())
    return;

  (*it)->onDetach();

  m_layers.erase(it);
}

} // namespace Engine
