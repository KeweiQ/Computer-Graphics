// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  
  float theta = mod(animation_seconds, 8.0) * 2.0 * M_PI / 8.0;

  mat4 light_translate = mat4(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    6, 6, 0, 1);
  mat4 light_rotate = mat4(
    cos(theta), 0, sin(theta), 0,
    0, 1, 0, 0,
    -sin(theta), 0, cos(theta), 0,
    0, 0, 0, 1);
  vec4 light = view * light_rotate * light_translate * vec4(0.0, 0.0, 0.0, 1.0);

  vec3 ka, ks, kd;
  float p;
  vec3 n, v, l;

  if (is_moon) {
    ka = vec3(0.01, 0.01, 0.01);
    ks = vec3(0.9, 0.9, 0.9);
    kd = vec3(0.4, 0.4, 0.4);
    p = 500;
  } else {
    ka = vec3(0.01, 0.02, 0.05);
    ks = vec3(0.9, 0.9, 0.9);
    kd = vec3(0.15, 0.25, 0.8);
    p = 500;
  }

  n = normalize(normal_fs_in);
  v = -normalize(view_pos_fs_in.xyz);
  l = normalize(light.xyz - view_pos_fs_in.xyz);

  color = blinn_phong(ka, kd, ks, p, n, v, l);

  /////////////////////////////////////////////////////////////////////////////
}