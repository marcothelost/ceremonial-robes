#include "CRobes/Camera.hpp"

void crb::Camera::updatePosition(const float deltaTime)
{
  crb::Space::Vec3 movementFactor = crb::Space::normalize(this->movement) * this->speed * deltaTime;

  this->movement = {0.f, 0.f, 0.f};
  this->position += movementFactor;
}

void crb::Camera::updateMatrix()
{
  crb::Space::Mat4 view {1.f};
  crb::Space::Mat4 projection {1.f};
  
  view = crb::Space::translate(view, this->position);
  projection = crb::Space::perspective(
    this->fov,
    (float)this->bufferWidth / this->bufferHeight,
    this->zNear,
    this->zFar
  );

  this->matrix = view * projection;
}
