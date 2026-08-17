#pragma once

#include <engine/renderer/BufferElement.hpp>

#include <cstdint>
#include <initializer_list>
#include <vector>

namespace Engine {
class BufferLayout {
public:
  BufferLayout() = default;

  BufferLayout(const std::initializer_list<BufferElement> &elements);

  uint32_t getStride() const;

  const std::vector<BufferElement> &getElements() const;

  auto begin() const { return m_elements.begin(); }
  auto end() const { return m_elements.end(); }

private:
  void calculateOffsetsAndStride();

private:
  std::vector<BufferElement> m_elements;
  uint32_t m_stride = 0;
};
} // namespace Engine
