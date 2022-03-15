#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  
  // no keyframe, return zero vector
  if (keyframes.size() == 0) {
    return Eigen::Vector3d::Zero();
  }

  // one frame, image stay still
  if (keyframes.size() == 1) {
    return keyframes.front().second;
  }

  // calculate index of frame in a loop
  double t_frame = keyframes.front().first + std::fmod(t, keyframes.back().first - keyframes.front().first);

  // find the closest keyframe
  int i;
  for (i = 0; i < keyframes.size(); i++) {
    if (keyframes[i].first > t_frame) {
      break;
    } else if (keyframes[i].first == t_frame) {
      return keyframes[i].second;
    }
  }

  // linear interpolation for boundaries
  if (i < 2 || i > keyframes.size() - 2) {
    double t0, t1;
    t0 = keyframes[i-1].first;
    t1 = keyframes[i].first;

    Eigen::Vector3d theta0, theta1;
    theta0 = keyframes[i-1].second;
    theta1 = keyframes[i].second;

    double T = (t_frame - t0) / (t1 - t0);
    return theta0 + T * (theta1 - theta0);
  }
   
  // get key-times about 4 keyframes
  double t0, t1, t2, t3;
  t0 = keyframes[i - 2].first;
  t1 = keyframes[i - 1].first;
  t2 = keyframes[i].first;
  t3 = keyframes[i + 1].first;

  // get correcponding key-values
  Eigen::Vector3d theta0, theta1, theta2, theta3;
  theta0 = keyframes[i - 2].second;
  theta1 = keyframes[i - 1].second;
  theta2 = keyframes[i].second;
  theta3 = keyframes[i + 1].second;

  // source: https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull%E2%80%93Rom_spline
  // calculate tangent of 2 pairs of keyframes
  Eigen::Vector3d m1, m2;
  m1 = (theta2 - theta0) / (t2 - t0);
  m2 = (theta3 - theta1) / (t3 - t1);

  // calculate interval substitute
  double T = (t_frame - t1) / (t2 - t1);

  // calculate c(t)
  double T2 = T * T;
  double T3 = T * T * T;
  Eigen::Vector3d ct = (2 * T3 - 3 * T2 + 1) * theta1 + (T3 - 2 * T2 + T) * m1 + (-2 * T3 + 3 * T2) * theta2 + (T3 - T2) * m2;

  return ct;

  /////////////////////////////////////////////////////////////////////////////
}
