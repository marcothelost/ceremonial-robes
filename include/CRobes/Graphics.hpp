#ifndef CRB_GRAPHICS_HPP
#define CRB_GRAPHICS_HPP

#include <GL/glew.h>
#include <string>

#include "Constants.hpp"
#include "File.hpp"

namespace crb
{
  /**
   * @brief Contains functions related to graphics rendering in the Ceremonial Robes Engine.
   */
  namespace Graphics
  {
    /**
     * @brief Sets the OpenGL rendering mode to point mode.
     */
    inline void usePointMode()
    { glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); }
    /**
     * @brief Sets the OpenGL rendering mode to line mode.
     */
    inline void useLineMode()
    { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
    /**
     * @brief Sets the OpenGL rendering mode to fill mode.
     */
    inline void useFillMode()
    { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

    /**
     * @class Shader
     * @brief Encapsulates OpenGL shader functionality.
     * 
     * This class manages loading, compiling, and using shaders
     * in OpenGL. It provides methods to load shader files, 
     * compile them, activate for rendering, and delete them 
     * when they're no longer needed.
     */
    class Shader
    {
      public:
        /**
         * @brief Constructs a Shader object by loading and compiling the specified vertex and fragment shader files.
         *
         * @param vertexPath The file path to the vertex shader source code.
         * @param fragmentPath The file path to the fragment shader source code.
         */
        Shader(const std::string& vertexPath, const std::string& fragmentPath);

        /**
         * @brief Activates the shader program for use.
         */
        void Use()
        { glUseProgram(this->ID); }
        /**
         * @brief Deletes the shader program, releasing associated OpenGL resources.
         */
        void Delete()
        { glDeleteProgram(this->ID); }

      private:
        GLuint ID;
    };

    /**
     * @class VBO
     * @brief Encapsulates an OpenGL Vertex Buffer Object (VBO).
     * 
     * This class provides functionalities for creating, binding, unbinding,
     * and deleting a Vertex Buffer Object in OpenGL. VBOs are used to store
     * vertex data in GPU memory for efficient rendering.
     */
    class VBO
    {
      public:
        /**
         * @brief Constructs a VBO object with the specified vertex data.
         *
         * @param vertices An array of GLfloat containing vertex data.
         * @param verticesSize The size of the vertex data array.
         */
        VBO(GLfloat vertices[], GLsizeiptr verticesSize);

        /**
         * @brief Binds the VBO.
         */
        void Bind()
        { glBindBuffer(GL_ARRAY_BUFFER, this->ID); }
        /**
         * @brief Unbinds the VBO.
         */
        void Unbind()
        { glBindBuffer(GL_ARRAY_BUFFER, 0); }
        /**
         * @brief Deletes the VBO, releasing associated OpenGL resources.
         */
        void Delete()
        { glDeleteBuffers(1, &this->ID); }

      private:
        GLuint ID;
    };

    /**
     * @class EBO
     * @brief Encapsulates an OpenGL Element Buffer Object (EBO).
     * 
     * This class provides functionalities for creating, binding, unbinding,
     * and deleting an Element Buffer Object in OpenGL. EBOs are used to store
     * indices that reference vertices in VBOs for efficient rendering.
     */
    class EBO
    {
      public:
        /**
         * @brief Constructs an EBO object with the specified indices.
         *
         * @param indices An array of GLuint containing index data.
         * @param indicesSize The size of the index data array.
         */
        EBO(GLuint indices[], GLsizeiptr indicesSize);

        /**
         * @brief Binds the EBO.
         */
        void Bind()
        { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID); }
        /**
         * @brief Unbinds the EBO.
         */
        void Unbind()
        { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
        /**
         * @brief Deletes the EBO, releasing associated OpenGL resources.
         */
        void Delete()
        { glDeleteBuffers(1, &this->ID); }

      private:
        GLuint ID;
    };
  }
}

#endif // CRB_GRAPHICS_HPP
