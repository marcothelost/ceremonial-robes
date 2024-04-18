#include "CRobes/Constants.hpp"
#include "CRobes/Space.hpp"

crb::Space::Mat4 crb::Space::ortho(const float left, const float right, const float top, const float bottom, const float zNear, const float zFar)
{
  crb::Space::Mat4 result {1.f};
  result[0][0] =  2.f / (right - left);
  result[1][1] =  2.f / (top - bottom);
  result[2][2] = -2.f / (zFar - zNear);
  result[3][0] = -(right + left) / (right - left);
  result[3][1] = -(top + bottom) / (top - bottom);
  result[3][2] = -(zFar + zNear) / (zFar - zNear);
  return result;
}

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

crb::Space::Mat4 crb::Space::lookAt(const crb::Space::Vec3& eye, const crb::Space::Vec3& target, const crb::Space::Vec3& up)
{
  crb::Space::Vec3 front = crb::Space::normalize(eye - target);
  crb::Space::Vec3 right = crb::Space::normalize(crb::Space::cross(up, front));
  crb::Space::Vec3 newUp = crb::Space::cross(front, right);
  crb::Space::Mat4 result;

  result[0][0] = right.x;
  result[1][0] = right.y;
  result[2][0] = right.z;
  result[0][1] = newUp.x;
  result[1][1] = newUp.y;
  result[2][1] = newUp.z;
  result[0][2] = front.x;
  result[1][2] = front.y;
  result[2][2] = front.z;
  result[3][0] = -crb::Space::dot(right, eye);
  result[3][1] = -crb::Space::dot(newUp, eye);
  result[3][2] = -crb::Space::dot(front, eye);
  result[3][3] = 1.f;

  return result;
}
