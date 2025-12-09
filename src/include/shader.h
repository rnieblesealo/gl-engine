#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

namespace gle
{
class Shader
{
public:
  Shader(std::string const &vertex_shader_path, std::string const &fragment_shader_path);
  ~Shader();

  void   WriteUniformMat4(std::string const &uniform_name, glm::mat4 const &new_value);
  bool   Validate(GLuint vao);
  GLuint GetShaderIndex();

private:
  GLuint _shader;

  GLuint _CompileShader(std::string const &shader_code, GLenum shader_type);
  void   _LinkProgram();
};
} // namespace gle
