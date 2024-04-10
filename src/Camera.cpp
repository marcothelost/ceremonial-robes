#include "CRobes/Camera.hpp"

void crb::Camera::updatePosition(const float deltaTime)
{
  const float usedSpeed = this->speed * deltaTime;

  this->position += -this->movement.x * crb::Space::cross(this->front, this->up) * usedSpeed;
  this->position += this->movement.z * this->front * usedSpeed;
  this->position.y += this->movement.y * usedSpeed;

  this->movement = {0.f, 0.f, 0.f};
}

void crb::Camera::updateRotation(const std::pair<float, float>& mousePosition)
{
  float deltaX = mousePosition.first - (float)this->bufferWidth / 2.f;
  float deltaY = mousePosition.second - (float)this->bufferHeight / 2.f;

  this->yaw += deltaX * this->sensitivity;
  this->pitch -= deltaY * this->sensitivity;

  if (this->pitch > 89.9f)
  {
    this->pitch = 89.9f;
  }
  if (this->pitch < -89.9f)
  {
    this->pitch = -89.9f;
  }
  this->yaw = std::remainderf(this->yaw, 360.f);
}

void crb::Camera::updateMatrix()
{
  crb::Space::Vec3 tempFront {0.f};

  const float sinYaw = sinf(crb::Space::radians(this->yaw));
  const float cosYaw = cosf(crb::Space::radians(this->yaw));
  const float cosPitch = cosf(crb::Space::radians(this->pitch));

  tempFront.x = cosYaw * cosPitch;
  tempFront.y = sinf(crb::Space::radians(this->pitch));
  tempFront.z = sinYaw * cosPitch;

  this->front = {
    cosYaw,
    0.f,
    sinYaw,
  };

  crb::Space::Mat4 view {1.f};
  crb::Space::Mat4 projection {1.f};
  
  if (this->using3D)
  {
    view = crb::Space::lookAt(
      this->position,
      this->position + tempFront,
      this->up
    );
  }
  projection = this->using3D
    ? crb::Space::perspective(
      this->fov,
      (float)this->bufferWidth / this->bufferHeight,
      this->zNear,
      this->zFar
    ) : crb::Space::ortho(
      0,
      this->bufferWidth,
      0,
      this->bufferHeight,
      -1.f,
      1.f
    );

  this->matrix = view * projection;
}
