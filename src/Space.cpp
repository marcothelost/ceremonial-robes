#include "CRobes/Space.hpp"

crb::Space::Mat4 crb::Space::perspective(const float fov, const float aspect, const float zNear, const float zFar)
{
  const float halfTanFOV = tanf(crb::Space::radians(fov) / 2.f);
  crb::Space::Mat4 result;

  result[0][0] = 1.f / (aspect * halfTanFOV);
  result[1][1] = 1.f / halfTanFOV;
  result[2][2] = (zFar + zNear) / (zNear - zFar);
  result[2][3] = -1.f;
  result[3][2] = -(2 * zFar * zNear) / (zFar - zNear);

  return result;
}
