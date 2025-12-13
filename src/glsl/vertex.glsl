#version 410 core // Metal 4.1

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 in_texcoord;

out vec2 texcoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
  texcoord = in_texcoord;
  gl_Position = projection * view * model * vec4(pos, 1.0f);
}
