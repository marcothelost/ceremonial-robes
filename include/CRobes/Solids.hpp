#ifndef CRB_SOLIDS_HPP
#define CRB_SOLIDS_HPP

#include <GL/glew.h>

#include "Graphics.hpp"
#include "Space.hpp"

namespace crb
{
  /**
   * @brief Namespace containing classes and utilities for rendering solid objects in the Ceremonial Robes Engine.
   */
  namespace Solids
  {
    /**
     * @brief A class representing a solid object in 3D space.
     */
    class Solid
    {
      public:
        /**
         * @brief Constructs a Solid object with the specified parameters.
         * 
         * @param position The position of the solid object.
         * @param VAO The vertex array object (VAO) associated with the object's geometry.
         * @param VBO The vertex buffer object (VBO) containing the object's vertex data.
         * @param EBO The element buffer object (EBO) containing the object's index data.
         * @param vertexCount The number of vertices in the object's geometry.
         */
        Solid(const crb::Space::Vec3& position, const crb::Graphics::VAO VAO, const crb::Graphics::VBO VBO, const crb::Graphics::EBO EBO, const GLuint vertexCount)
        : position(position), VAO(VAO), VBO(VBO), EBO(EBO), vertexCount(vertexCount)
        {}
        /**
         * @brief Destructor to release associated OpenGL resources.
         */
        ~Solid()
        {
          this->VAO.Delete();
          this->VBO.Delete();
          this->EBO.Delete();
        }

        /**
         * @brief Renders the solid object using the specified shader program.
         * 
         * @param shader The shader program to use for rendering.
         */
        virtual void render(const crb::Graphics::Shader& shader) const;

      private:
        crb::Space::Mat4 model    {1.f};
        crb::Space::Vec3 position {0.f};

        crb::Graphics::VAO VAO;
        crb::Graphics::VBO VBO;
        crb::Graphics::EBO EBO;

        GLuint vertexCount {0};
    };
  }
}

#endif // CRB_SOLIDS_HPP
