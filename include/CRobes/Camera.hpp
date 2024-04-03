#ifndef CRB_CAMERA_HPP
#define CRB_CAMERA_HPP

#include <GL/glew.h>

#include "Graphics.hpp"
#include "Space.hpp"

namespace crb
{
  /**
   * @brief A class representing a camera in a 3D scene.
   */
  class Camera
  {
    public:
      /**
       * @brief Constructs a Camera object with the specified parameters.
       * 
       * @param fov The field of view angle in degrees.
       * @param bufferWidth The width of the buffer.
       * @param bufferHeight The height of the buffer.
       * @param zNear The near clipping plane.
       * @param zFar The far clipping plane.
       * @param speed The movement speed of the camera.
       * @param sensitivity The sensitivity of the camera controls.
       */
      Camera(const float fov, const float bufferWidth, const float bufferHeight, const float zNear, const float zFar, const float speed, const float sensitivity)
      : fov(fov), bufferWidth(bufferWidth), bufferHeight(bufferHeight), zNear(zNear), zFar(zFar), speed(speed)
      {}

      /**
       * @brief Sets the field of view angle of the camera.
       * 
       * @param fov The field of view angle in degrees.
       */
      void setFov(const float fov)
      { this->fov = fov; }
      /**
       * @brief Sets the width of the buffer associated with the camera.
       * 
       * @param bufferWidth The width of the buffer.
       */
      void setBufferWidth(const unsigned int bufferWidth)
      { this->bufferWidth = bufferWidth; }
      /**
       * @brief Sets the height of the buffer associated with the camera.
       * 
       * @param bufferHeight The height of the buffer.
       */
      void setBufferHeight(const unsigned int bufferHeight)
      { this->bufferHeight = bufferHeight; }
      /**
       * @brief Sets the movement speed of the camera.
       * 
       * @param speed The movement speed.
       */
      void setSpeed(const float speed)
      { this->speed = speed; }
      /**
       * @brief Sets the movement vector of the camera.
       * 
       * @param movement The movement vector.
       */
      void setMovement(const crb::Space::Vec3& movement)
      { this->movement = movement; }

      /**
       * @brief Updates the position of the camera based on its movement and deltaTime.
       * 
       * @param deltaTime The time elapsed since the last update.
       */
      void updatePosition(const float deltaTime);
      /**
       * @brief Updates the rotation of the camera based on the mouse position.
       * 
       * @param mousePosition The current mouse position.
       */
      void updateRotation(const std::pair<float, float>& mousePosition);
      /**
       * @brief Updates the camera's projection matrix.
       */
      void updateMatrix();
      /**
       * @brief Applies the camera matrix to a shader.
       * 
       * @param shader The shader program to apply the matrix to.
       */
      void applyMatrix(const crb::Graphics::Shader& shader)
      { shader.SetMatrix4(this->matrix, "cameraMatrix"); }
  
    private:
      float fov          {60.f};
      float bufferWidth  {1.f};
      float bufferHeight {1.f};
      float zNear        {0.1f};
      float zFar         {100.f};
      float speed        {5.f};
      float sensitivity  {0.1f};

      crb::Space::Mat4 matrix   {1.f};
      crb::Space::Vec3 position {0.f, 0.f, -3.f};
      crb::Space::Vec3 front    {0.f, 0.f, -1.f};
      crb::Space::Vec3 up       {0.f, 1.f, 0.f};
      crb::Space::Vec3 movement {0.f};

      float yaw   {90.f};
      float pitch {0.f};
  };
}

#endif // CRB_CAMERA_HPP
