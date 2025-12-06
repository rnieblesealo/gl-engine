#version 410 core // Metal 4.1

layout(location = 0) in vec3 pos;

uniform float x_move;

void main() {
  gl_Position = vec4(
      pos.x * 0.5 + x_move,
      pos.y * 0.5,
      pos.z,
      1.0
    );
}
