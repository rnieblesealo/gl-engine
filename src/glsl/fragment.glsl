#version 410 core

struct LightProperties {
  vec3 color;
  vec3 direction;
  float ambient_intensity;
  float diffuse_intensity;
};

struct MaterialProperties {
  float shininess;
  float specular_intensity;
};

in vec2 texcoord;
in vec3 normal;
in vec3 frag_pos;

out vec4 color;

uniform sampler2D sampler;
uniform LightProperties light_properties;
uniform MaterialProperties material_properties;
uniform vec3 eye_pos;

void main() {
  // Normalize everything
  vec3 N = normalize(normal);
  vec3 L = normalize(light_properties.direction);

  vec4 ambient_color = vec4(light_properties.color, 1.0f) * light_properties.ambient_intensity;

  float diffuse_factor = clamp(dot(N, L), 0.0f, 1.0f);
  vec4 diffuse_color = vec4(light_properties.color, 1.0f) * light_properties.diffuse_intensity * diffuse_factor;

  vec4 specular_color = vec4(0, 0, 0, 0);

  // If there isn't even diffuse light there can't be specular light! Keep it at 0
  if (diffuse_factor > 0) {
    // If these 2 are perfectly parallel we will see bright white
    vec3 frag_to_eye = eye_pos - frag_pos;
    vec3 R = normalize(reflect(L, N));

    float specular_factor = dot(frag_to_eye, R);
    if (specular_factor > 0) {
      specular_factor = pow(specular_factor, material_properties.shininess);
      specular_color = vec4(light_properties.color * material_properties.specular_intensity * specular_factor, 1.0f);
    }

    color = texture(sampler, texcoord) * (ambient_color + diffuse_color + specular_color);
  }
}
