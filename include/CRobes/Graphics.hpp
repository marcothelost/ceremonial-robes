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
  }
}

#endif // CRB_GRAPHICS_HPP
