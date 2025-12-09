#pragma once

#include <GL/glew.h> // WARNING: This needs to be included before GLFW due to conflicts
#include <GLFW/glfw3.h>
#include <array>

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

  // Keyboard
  std::array<bool, 1024> _keys{false};

  // Mouse
  float _last_x{0};
  float _last_y{0};
  float _dx{0};
  float _dy{0};
  bool  _first_mouse_move{false};

  static void _HandleKeys(GLFWwindow *window, int key, int code, int action, int mode);
  static void _HandleMouse(GLFWwindow *window, double x_pos, double y_pos);
};
}; // namespace gle
