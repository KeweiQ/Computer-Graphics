// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
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
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  
  // light
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

  // bump
  vec3 T, B;
  tangent(normalize(sphere_fs_in), T, B);
  
  vec3 b_sphere_fs_in = bump_position(is_moon, sphere_fs_in);
  vec3 perceived_n = cross((bump_position(is_moon, sphere_fs_in + T * 0.0001) - bump_position(is_moon, sphere_fs_in)) / 0.0001, 
  	(bump_position(is_moon, sphere_fs_in + B * 0.0001) - bump_position(is_moon, sphere_fs_in)) / 0.0001);
  if (dot(sphere_fs_in, perceived_n) < 0){
    perceived_n = -perceived_n;
  }
  vec3 bumped_normal = (transpose(inverse(view)) * transpose(inverse(model(is_moon, animation_seconds))) * vec4(normalize(perceived_n), 1.0)).xyz;

  // color
  float shore = 0.001;
  float plane = 0.7;
  float plateau = 0.9;
  float height = 30 * bump_height(is_moon, sphere_fs_in);

  vec3 ka, ks, kd;
  float p;
  vec3 n, v, l;
  
  if (is_moon) {
    ka = vec3(0.05, 0.05, 0.05);
    kd = vec3(0.6, 0.6, 0.6);
    ks = vec3(0.7, 0.7, 0.7);
    p = 200;

  } else {
    // mid value
    // ka = vec3(0.01, 0.05, 0.02);
    // kd = vec3(0.3, 0.8, 0.5);
    // ks = vec3(0.7, 0.7, 0.7);

    if (height < shore) {
      ka = vec3(0.01, 0.02, 0.05);
      kd = vec3(0.3, 0.4, 0.9);
      ks = vec3(0.7, 0.7, 0.7);

    } else if (height < plane) {
      ka = vec3(0.01, 0.05, 0.02);
      kd = vec3(0.3, 0.4 * improved_smooth_step(height) + 0.4, 0.4 * improved_smooth_step(-1.0 * height) + 0.5);
      ks = vec3(0.7, 0.7, 0.7);

    } else if (height < plateau) {
      ka = vec3(0.01, 0.05, 0.02);
      kd = vec3(0.4 * improved_smooth_step(height) + 0.3, 0.8, 0.4 * improved_smooth_step(-1.0 * height) + 0.1);
      ks = vec3(0.7, 0.7, 0.7);

    } else {
      ka = vec3(0.04, 0.04, 0.01);
      kd = vec3(0.7, 0.8, 0.1);
      ks = vec3(0.7, 0.7, 0.7);

    }
    p = 100;
  }

  n = normalize(bumped_normal);
  v = -normalize(view_pos_fs_in.xyz);
  l = normalize(light.xyz - view_pos_fs_in.xyz);

  color = blinn_phong(ka, kd, ks, p, n, v, l);
  
  // cloud
  if (!is_moon) {
    vec3 cloud_shape = vec3(1.0, 6.0, 1.0);
    float cloud_seed = 0.01 * sin(M_PI * animation_seconds);
    vec3 cloud_rotation = (rotate_about_y(mod(animation_seconds, 4.0) * 2 * M_PI / 4.0) * vec4(sphere_fs_in, 1)).xyz;
    float cloud_noise = improved_perlin_noise((1.5 + cloud_seed) * cloud_shape * cloud_rotation);

    if (cloud_noise > 0.01) {
      ka = vec3(0.1, 0.1, 0.1) * cloud_noise;
      kd = vec3(1.0, 1.0, 1.0) * cloud_noise;
      ks = vec3(0.0, 0.0, 0.0);

      n = normalize(normal_fs_in);
      vec3 cloud_color = blinn_phong(ka, kd, ks, p, n, v, l);
      color += 3.0 * cloud_color;
    }
  }

  /////////////////////////////////////////////////////////////////////////////
}
