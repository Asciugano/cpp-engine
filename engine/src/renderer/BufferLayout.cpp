#include <engine/renderer/BufferLayout.hpp>

namespace Engine {

BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &elements)
    : m_elements(elements) {
  calculateOffsetsAndStride();
}

void BufferLayout::calculateOffsetsAndStride() {
  uint32_t offset = 0;
  m_stride = 0;

  for (auto &element : m_elements) {
    element.offset = offset;

    offset += element.size;
    m_stride += element.size;
  }
}

uint32_t BufferLayout::getStride() const { return m_stride; }

const std::vector<BufferElement> &BufferLayout::getElements() const {
  return m_elements;
}

} // namespace Engine
