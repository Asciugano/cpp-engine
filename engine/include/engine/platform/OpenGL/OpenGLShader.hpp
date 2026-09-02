#pragma once

#include "glbinding/gl/types.h"
#include <engine/renderer/Shader.hpp>

#include <glbinding/gl/gl.h>

#include <string>
#include <unordered_map>

namespace Engine {

class OpenGLShader final : public Shader {
public:
  OpenGLShader(const std::string &vertexPath, const std::string &fragmentPath);

  ~OpenGLShader() override;

  OpenGLShader(const OpenGLShader &) = delete;
  OpenGLShader &operator=(const OpenGLShader &) = delete;

  OpenGLShader(OpenGLShader &&) = delete;
  OpenGLShader &operator=(OpenGLShader &&) = delete;

  void bind() const override;
  void unbind() const override;

  void setInt(const std::string &name, int value) override;

  void setFloat(const std::string &name, float value) override;

  void setVec2(const std::string &name, const glm::vec2 &value) override;

  void setVec3(const std::string &name, const glm::vec3 &value) override;

  void setVec4(const std::string &name, const glm::vec4 &value) override;

  void setMat4(const std::string &name, const glm::mat4 &value) override;

private:
  gl::GLint getUniformLocation(const std::string &name);

  static std::string readFile(const std::string &path);

  static gl::GLuint compileShader(gl::GLenum type, const std::string &source);

  static gl::GLuint createProgram(const std::string &vertexSource,
                                  const std::string &fragmentSource);

private:
  gl::GLuint m_rendererID = 0;
  std::unordered_map<std::string, gl::GLint> m_uniformLocations;
};

} // namespace Engine
