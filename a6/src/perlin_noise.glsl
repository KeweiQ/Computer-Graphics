// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
float perlin_noise(vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  
  // algorithm: https://flafla2.github.io/2014/08/09/perlinnoise.html
  vec3 min_corner = floor(st);
  vec3 max_corner = ceil(st);
  vec3 local_point = fract(st);
  vec3 smoothed_point = smooth_step(local_point);

  vec3 p000 = min_corner;
  vec3 p100 = min_corner + vec3(1, 0, 0);
  vec3 p110 = min_corner + vec3(1, 1, 0);
  vec3 p010 = min_corner + vec3(0, 1, 0);
  vec3 p001 = min_corner + vec3(0, 0, 1);
  vec3 p101 = min_corner + vec3(1, 0, 1);
  vec3 p111 = min_corner + vec3(1, 1, 1);
  vec3 p011 = min_corner + vec3(0, 1, 1);

  vec3 g000 = random_direction(p000);
  vec3 g100 = random_direction(p100);
  vec3 g110 = random_direction(p110);
  vec3 g010 = random_direction(p010);
  vec3 g001 = random_direction(p001);
  vec3 g101 = random_direction(p101);
  vec3 g111 = random_direction(p111);
  vec3 g011 = random_direction(p011);

  vec3 d000 = st - p000;
  vec3 d100 = st - p100;
  vec3 d110 = st - p110;
  vec3 d010 = st - p010;
  vec3 d001 = st - p001;
  vec3 d101 = st - p101;
  vec3 d111 = st - p111;
  vec3 d011 = st - p011;

  float i000 = dot(d000, g000);
  float i100 = dot(d100, g100);
  float i110 = dot(d110, g110);
  float i010 = dot(d010, g010);
  float i001 = dot(d001, g001);
  float i101 = dot(d101, g101);
  float i111 = dot(d111, g111);
  float i011 = dot(d011, g011);

  float mix_x1 = mix(i000, i100, smoothed_point.x);
  float mix_x2 = mix(i010, i110, smoothed_point.x);
  float mix_y1 = mix(mix_x1, mix_x2, smoothed_point.y);

  float mix_x3 = mix(i001, i101, smoothed_point.x);
  float mix_x4 = mix(i011, i111, smoothed_point.x);
  float mix_y2 = mix(mix_x3, mix_x4, smoothed_point.y);

  float mix_z = mix(mix_y1, mix_y2, smoothed_point.z);

  return mix_z / sqrt(3);

  /////////////////////////////////////////////////////////////////////////////
}

