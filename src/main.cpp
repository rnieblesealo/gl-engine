#include "camera.h"
#include "light.h"
#include "material.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gle
{
const std::filesystem::path VERTEX_SHADER_PATH("glsl/vertex.glsl");
const std::filesystem::path FRAGMENT_SHADER_PATH("glsl/fragment.glsl");

const std::filesystem::path METAL_TEXTURE_PATH("assets/metal.jpg");

float tri_rot       = 0.0f; // Current tri rotation
float tri_rot_delta = 0.0f; // Rotate by this angle every frame

void CalcAverageNormals(std::vector<GLfloat> &vertices,
                        uint32_t              v_size,
                        std::vector<GLuint>  &indices,
                        uint32_t              n_offset)
{
  for (int i = 0; i < indices.size(); i += 3)
  {
    // Compute indices to vertices comprising this face
    uint32_t in0 = indices[i] * v_size;
    uint32_t in1 = indices[i + 1] * v_size;
    uint32_t in2 = indices[i + 2] * v_size;

    // Compute 2 edges of the face
    glm::vec3 v1(
        vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);

    glm::vec3 v2(
        vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);

    // Get the face normal from their cross product
    glm::vec3 norm(glm::cross(v1, v2));
    norm = glm::normalize(norm);

    // Add the normal to each of the face vertices
    in0 += n_offset;
    in1 += n_offset;
    in2 += n_offset;

    vertices[in0] += norm.x;
    vertices[in0 + 1] += norm.y;
    vertices[in0 + 2] += norm.z;

    vertices[in1] += norm.x;
    vertices[in1 + 1] += norm.y;
    vertices[in1 + 2] += norm.z;

    vertices[in2] += norm.x;
    vertices[in2 + 1] += norm.y;
    vertices[in2 + 2] += norm.z;
  }

  for (int i = 0; i < vertices.size() / v_size; ++i)
  {
    uint32_t offset = i * v_size * n_offset;

    glm::vec3 vec(vertices[n_offset], vertices[n_offset + 1], vertices[n_offset + 2]);
    vec = glm::normalize(vec);

    vertices[n_offset]     = vec.x;
    vertices[n_offset + 1] = vec.y;
    vertices[n_offset + 2] = vec.z;
  }
}
} // namespace gle

int main()
{
  gle::Window window;

  gle::Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 2.0f, 0.1f);
  gle::Light  light(1.0f, 1.0f, 1.0f, glm::vec3(2.0f, -1.0f, -2.0f), 0.1f, 0.5f);

  gle::Shader   s_phong(gle::Shader(gle::VERTEX_SHADER_PATH, gle::FRAGMENT_SHADER_PATH));
  gle::Texture  t_metal(gle::METAL_TEXTURE_PATH);
  gle::Material pyramid_material(s_phong, t_metal, 0.6f, 10.0f); // Material with Phong shading and metallic texture

  // clang-format off
  std::vector<GLfloat> pyramid_vertices = {
  //    x      y     z       u     v      nx    ny    nz
    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 0.0f,   1.0f, 0.0f,   0.0f, 0.0f, 0.0f,
     0.0f,  1.0f, 0.0f,   1.0f, 1.0f,   0.0f, 0.0f, 0.0f,
     0.0f, -1.0f, 1.0f,   0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
  };

  // These form a shitty pyramid :)
  std::vector<GLuint> pyramid_indices = {
    0, 3, 1,
    1, 3, 2,
    2, 3, 0,
    0, 1, 2
  };
  // clang-format on

  gle::CalcAverageNormals(pyramid_vertices, 8, pyramid_indices, 5);

  gle::Mesh pyramid(pyramid_vertices, pyramid_indices, pyramid_material);

  auto then = std::chrono::high_resolution_clock::now(); // Initial time for deltatime computation

  while (!glfwWindowShouldClose(window.GetHandle()))
  {
    // UPDATE ---------------------------------------------------------------------------------------------------------

    glfwPollEvents();

    // Compute delta time in seconds
    // Std. chrono provides high-res clock for this
    auto  now        = std::chrono::high_resolution_clock::now();
    float delta_time = std::chrono::duration<float, std::chrono::seconds::period>(now - then).count();
    then             = now;

    // Camera movement
    camera.KeyControl(window, delta_time);
    camera.MouseControl(window);

    // Update framebuffer size to keep aspect corrected
    window.PollFramebufferSize();
    glViewport(0, 0, window.GetFramebufferWidth(), window.GetFramebufferHeight()); // Must update viewport to match!

    glm::float32 window_aspect =
        static_cast<GLfloat>(window.GetFramebufferWidth()) / static_cast<GLfloat>(window.GetFramebufferHeight());

    // DRAW CALLS -----------------------------------------------------------------------------------------------------

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // clang-format off
    pyramid_material.UseMaterial();
      light.WriteLightProperties(pyramid_material.GetShader()); // TODO: I don't like that we have to pass shader but ok. 
      camera.WriteEyePosition(pyramid_material.GetShader());
      camera.WriteViewMatrix(pyramid_material.GetShader());
      camera.WriteProjectionMatrix(pyramid_material.GetShader(), window_aspect);
      pyramid.Draw();
    // clang-format on

    glfwSwapBuffers(window.GetHandle());
  }
} // namespace gle
