#pragma once

#include <engine/renderer/Shader.hpp>

namespace Engine {
class OpenGLShader : public Shader {
public:
  OpenGLShader(const std::string &vertexPath, const std::string &fragmentPath);

  ~OpenGLShader() override;

  void bind() const override;
  void unbind() const override;

private:
  unsigned int m_rendererID = 0;
};
} // namespace Engine
