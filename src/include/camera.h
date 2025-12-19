#pragma once

#include "shader.h"
#include "window.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace gle
{
class Camera
{
public:
  Camera(glm::vec3 start_position,
         glm::vec3 start_up,
         GLfloat   start_yaw,
         GLfloat   start_pitch,
         GLfloat   start_movement_speed,
         GLfloat   start_look_speed);
  ~Camera();

  void KeyControl(Window &window, float delta_time);
  void MouseControl(Window &window);

  glm::mat4 CalculateViewMatrix();
  glm::vec3 GetPosition();

  void WriteEyePosition(Shader &shader);
  void WriteViewMatrix(Shader &shader);
  void WriteProjectionMatrix(Shader &shader, glm::float32 aspect);

private:
  glm::vec3 _position;
  glm::vec3 _front;
  glm::vec3 _up;
  glm::vec3 _right;
  glm::vec3 _world_up;

  GLfloat _yaw;
  GLfloat _pitch;
  GLfloat _movement_speed;
  GLfloat _look_speed;

  // PROJECTION
  glm::float32 _fov;
  glm::float32 _near;
  glm::float32 _far;

  void _Update();
};
} // namespace gle
