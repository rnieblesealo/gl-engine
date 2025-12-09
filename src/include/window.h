#pragma once

#include <GL/glew.h> // WARNING: This needs to be included before GLFW due to conflicts
#include <GLFW/glfw3.h>

namespace gle
{
class Window final
{
public:
  Window();
  ~Window();

  GLFWwindow *GetHandle();
  void        PollFramebufferSize();
  GLsizei     GetFramebufferWidth();
  GLsizei     GetFramebufferHeight();

private:
  GLFWwindow *_window;
  GLsizei     _fb_width;
  GLsizei     _fb_height;
};
}; // namespace gle
