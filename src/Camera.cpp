#include "CRobes/Camera.hpp"

void crb::Camera::updateMatrix()
{
  crb::Space::Mat4 view {1.f};
  crb::Space::Mat4 projection = crb::Space::perspective(
    this->fov,
    (float)this->bufferWidth / this->bufferHeight,
    this->zNear,
    this->zFar
  );

  this->matrix = projection * view;
}
