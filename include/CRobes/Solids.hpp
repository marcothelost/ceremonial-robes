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
         * @param position The position of the solid in 3D space.
         * @param vertices An array of GLfloat containing vertex data.
         * @param verticesSize The size of the vertex data array.
         * @param indices An array of GLuint containing index data.
         * @param indicesSize The size of the index data array.
         */
        Solid(const crb::Space::Vec3& position, GLfloat vertices[], GLsizeiptr verticesSize, GLuint indices[], GLsizeiptr indicesSize);
        /**
         * @brief Destructor to release associated OpenGL resources.
         */
        ~Solid()
        {
          if (this->VAO != NULL) this->VAO->Delete();
          if (this->VBO != NULL) this->VBO->Delete();
          if (this->EBO != NULL) this->EBO->Delete();
        }
        /**
         * @brief Move constructor for Solid objects.
         *
         * @param other Another Solid object.
         */
        Solid(crb::Solids::Solid&& other)
        {
          this->VAO = other.VAO;
          this->VBO = other.VBO;
          this->EBO = other.EBO;
          this->position = other.position;
          this->vertexCount = other.vertexCount;
          
          other.VAO = NULL;
          other.VBO = NULL;
          other.EBO = NULL;
          other.position = {0.f};
          other.vertexCount = 0;
        }
        /**
         * @brief Copy constructor for Solid objects.
         *
         * @param other Another Solid object.
         */
        Solid(const crb::Solids::Solid& other)
        {
          this->VAO = (other.VAO != NULL) ? new crb::Graphics::VAO(*other.VAO) : NULL;
          this->VBO = (other.VBO != NULL) ? new crb::Graphics::VBO(*other.VBO) : NULL;
          this->EBO = (other.EBO != NULL) ? new crb::Graphics::EBO(*other.EBO) : NULL;
        
          this->position = other.position;
          this->vertexCount = other.vertexCount;
        }
        /**
         * @brief Copy assignment operator for Solid objects.
         *
         * @param other Another Solid object.
         * @return A reference to the assigned object.
         */
        crb::Solids::Solid& operator=(const crb::Solids::Solid& other)
        {
          if (this != &other)
          {
            if (this->VAO != NULL) delete this->VAO;
            if (this->VBO != NULL) delete this->VBO;
            if (this->EBO != NULL) delete this->EBO;

            this->VAO = (other.VAO != NULL) ? new crb::Graphics::VAO(*other.VAO) : NULL;
            this->VBO = (other.VBO != NULL) ? new crb::Graphics::VBO(*other.VBO) : NULL;
            this->EBO = (other.EBO != NULL) ? new crb::Graphics::EBO(*other.EBO) : NULL;
          
            this->position = other.position;
            this->vertexCount = other.vertexCount;
          }
          return *this;
        }

        /**
         * @brief Gets the position of the solid.
         * 
         * @return The position of the solid in 3D space.
         */
        crb::Space::Vec3 getPosition() const
        { return this->position; }
        /**
         * @brief Gets the x-coordinate of the solid's position.
         * 
         * @return The x-coordinate of the solid's position.
         */
        float getX() const
        { return this->position.x; }
        /**
         * @brief Gets the y-coordinate of the solid's position.
         * 
         * @return The y-coordinate of the solid's position.
         */
        float getY() const
        { return this->position.y; }
        /**
         * @brief Gets the z-coordinate of the solid's position.
         * 
         * @return The z-coordinate of the solid's position.
         */
        float getZ() const
        { return this->position.z; }

        /**
         * @brief Renders the solid object using the specified shader program.
         * 
         * @param shader The shader program to use for rendering.
         */
        void render(const crb::Graphics::Shader& shader, GLenum mode) const;

      private:
        crb::Space::Mat4 model    {1.f};
        crb::Space::Vec3 position {0.f};

        crb::Graphics::VAO* VAO {NULL};
        crb::Graphics::VBO* VBO {NULL};
        crb::Graphics::EBO* EBO {NULL};

        GLuint vertexCount {0};
    };

    /**
     * @brief A factory class for creating solid objects.
     */
    class SolidFactory
    {
      public:
        /**
         * @brief Default constructor.
         */
        SolidFactory()
        {}

        /**
         * @brief Creates a plane object.
         * 
         * Creates a plane object with the specified parameters.
         * 
         * @param position The position of the plane.
         * @param length The length of the plane.
         * @param width The width of the plane.
         * @param segmentCount The number of segments in the plane's geometry.
         * @return The created plane object.
         */
        crb::Solids::Solid createPlane(const crb::Space::Vec3& position, const float length, const float width, const unsigned int segmentCount);
    };
  }
}

#endif // CRB_SOLIDS_HPP
