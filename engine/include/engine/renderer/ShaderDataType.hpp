#pragma once

#include <cstdint>

namespace Engine {
enum class ShaderDataType {
  None = 0,

  Float,
  Float2,
  Float3,
  Float4,

  Mat3,
  Mat4,

  Int,
  Int2,
  Int3,
  Int4,

  Bool,
};

uint32_t shaderDataTypeSize(ShaderDataType type);
uint32_t shaderDataTypeComponentCount(ShaderDataType type);
} // namespace Engine
