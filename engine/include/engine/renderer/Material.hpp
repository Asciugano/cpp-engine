#pragma once

#include <engine/renderer/Shader.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <type_traits>

namespace Engine {
class Material {
public:
  explicit Material(std::unique_ptr<Shader> shader);
  Material(std::unique_ptr<Shader> shader, const glm::vec4 &color);

  Shader &getShader();
  const Shader &getShader() const;

  void setColor(const glm::vec4 &color);
  const glm::vec4 &getColor() const;

  void bind(const char *name = "u_Color") const;

  template <typename T> void setUniform(const char *name, const T &value) {

    using Type = std::remove_cvref_t<T>;

    if constexpr (std::is_same_v<Type, float>) {
      m_shader->setFloat(name, value);
    } else if constexpr (std::is_same_v<Type, int>) {
      m_shader->setInt(name, value);
    } else if constexpr (std::is_same_v<Type, glm::vec2>) {
      m_shader->setVec2(name, value);
    } else if constexpr (std::is_same_v<Type, glm::vec3>) {
      m_shader->setVec3(name, value);
    } else if constexpr (std::is_same_v<Type, glm::vec4>) {
      m_shader->setVec4(name, value);
    } else if constexpr (std::is_same_v<Type, glm::mat4>) {
      m_shader->setMat4(name, value);
    } else {
      static_assert(false, "Unsupported uniform type");
    }
  }

private:
  std::unique_ptr<Shader> m_shader;
  glm::vec4 m_color{1.0f};
};
} // namespace Engine
