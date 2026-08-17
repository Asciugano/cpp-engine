#include "glbinding/gl/enum.h"
#include "glbinding/gl/functions.h"
#include <engine/platform/OpenGL/OpenGLShader.hpp>
#include <glbinding/gl/gl.h>
#include <iostream>

namespace Engine {
static gl::GLuint compileShader(gl::GLenum type, const std::string &source) {
  gl::GLuint shader = gl::glCreateShader(type);

  const char *src = source.c_str();

  gl::glShaderSource(shader, 1, &src, nullptr);

  gl::glCompileShader(shader);

  gl::GLint success;
  gl::glGetShaderiv(shader, gl::GL_COMPILE_STATUS, &success);

  if (!success) {
    char infoLog[1024];

    gl::glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);

    std::cerr << "Shader compilation failed:" << std::endl
              << infoLog << std::endl;
  }

  return shader;
}

OpenGLShader::OpenGLShader(const std::string &vertexSource,
                           const std::string &fragmentSource) {

  gl::GLuint vertexShader = compileShader(gl::GL_VERTEX_SHADER, vertexSource);
  gl::GLuint fragmentShader =
      compileShader(gl::GL_FRAGMENT_SHADER, fragmentSource);

  m_rendererID = gl::glCreateProgram();

  gl::glAttachShader(m_rendererID, vertexShader);
  gl::glAttachShader(m_rendererID, fragmentShader);

  gl::glLinkProgram(m_rendererID);

  gl::glDeleteShader(vertexShader);
  gl::glDeleteShader(fragmentShader);
}

OpenGLShader::~OpenGLShader() { gl::glDeleteProgram(m_rendererID); }

void OpenGLShader::bind() const { gl::glUseProgram(m_rendererID); }

void OpenGLShader::unbind() const { gl::glUseProgram(0); }
} // namespace Engine
