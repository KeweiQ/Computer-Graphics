// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height(bool is_moon, vec3 s)
{
  /////////////////////////////////////////////////////////////////////////////
  
  if (is_moon) {
    float noise_big = improved_perlin_noise(sin(M_PI * s));
    float noise_small = improved_perlin_noise(1.5 * sin(M_PI * s));
    float noise_3 = improved_perlin_noise(2.0 * sin(M_PI * s));
    return 0.04 * smooth_heaviside(mix(noise_big, noise_small, noise_3), 10);

  } else {
    float noise_big = improved_perlin_noise(sin(M_PI * s));
    float noise_small = improved_perlin_noise(2.0 * sin(M_PI * s));
    float noise_3 = improved_perlin_noise(4.0 * sin(M_PI * s));
    return 0.05 * smooth_heaviside(mix(noise_big, noise_small, noise_3), 20);
  }
  
  /////////////////////////////////////////////////////////////////////////////
}
