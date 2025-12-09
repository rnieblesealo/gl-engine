#include "window.h"
#include <iostream>

namespace gle
{
constexpr GLint WINDOW_WIDTH  = 500;
constexpr GLint WINDOW_HEIGHT = 500;

Window::Window()
{
  if (glfwInit() != GLFW_TRUE)
  {
    std::cerr << "Error initializing GLFW" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL 3.3
  glfwWindowHint(GLFW_OPENGL_PROFILE,
                 GLFW_OPENGL_CORE_PROFILE);            // Use core profile; essentially disables backwards compat
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Enable forward compatibility

  this->_window = glfwCreateWindow(gle::WINDOW_WIDTH, gle::WINDOW_HEIGHT, "GLEngine", NULL, NULL);

  glfwMakeContextCurrent(this->_window);

  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK)
  {
    std::cerr << "Error initializing GLEW" << std::endl;

    glfwDestroyWindow(this->_window);
    glfwTerminate();

    std::exit(EXIT_FAILURE);
  }

  glfwGetFramebufferSize(this->_window, &this->_fb_width, &this->_fb_height);

  glViewport(0, 0, this->_fb_width, this->_fb_height);

  glEnable(GL_DEPTH_TEST);
}

Window::~Window()
{
  glfwDestroyWindow(this->_window);
  glfwTerminate();

  // TODO: Ensure stuff is unset properly as well (glfwMakeContextCurrent...)
}

GLFWwindow *Window::GetHandle() { return this->_window; }

void Window::PollFramebufferSize() { glfwGetFramebufferSize(this->_window, &this->_fb_width, &this->_fb_height); }

GLsizei Window::GetFramebufferWidth() { return this->_fb_width; }

GLsizei Window::GetFramebufferHeight() { return this->_fb_height; }
} // namespace gle
