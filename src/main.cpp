#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace
{
const GLint WIDTH         = 800;
const GLint WINDOW_HEIGHT = 600;
} // namespace

int main()
{
  // Start GLFW
  if (glfwInit() != GLFW_TRUE)
  {
    std::exit(EXIT_FAILURE);
  }

  // Setup GLFW window
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL 3.3
  glfwWindowHint(
      GLFW_OPENGL_PROFILE,
      GLFW_OPENGL_CORE_PROFILE); // Use core profile; essentially disables backwards compat
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Enable forward compatibility

  // Initialize window
  gsl::not_null<GLFWwindow *> main_window =
      glfwCreateWindow(WIDTH, WINDOW_HEIGHT, "GLEngine", NULL, NULL);

  // Get window framebuffer size
  glm::ivec2 fb_size;
  glfwGetFramebufferSize(main_window, &fb_size.x, &fb_size.y);

  // Set GLEW context
  // Essentially tell it that this window is the one bound to our OpenGL context
  // "Hey GLEW, draw stuff to this window!"
  glfwMakeContextCurrent(main_window);

  // Allow modern extensions
  glewExperimental = GL_TRUE;

  // Initialize GLEW
  if (glewInit() != GLEW_OK)
  {
    glfwDestroyWindow(main_window);
    glfwTerminate();

    std::exit(EXIT_FAILURE);
  }

  // Set viewport (draw area) to be full framebuffer
  glViewport(0, 0, fb_size.x, fb_size.y);

  // Main loop
  while (!glfwWindowShouldClose(main_window))
  {
    glfwPollEvents();

    glClearColor(0.5, 0.5, 0, 1); // Set background clear color
    glClear(GL_COLOR_BUFFER_BIT); // Clear background

    glfwSwapBuffers(main_window); // 2 buffer system
  }
}