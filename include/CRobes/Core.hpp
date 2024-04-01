#ifndef CRB_CORE_HPP
#define CRB_CORE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Constants.hpp"

namespace crb
{
  /**
   * @brief Contains functions related to the core functionality of the Ceremonial Robes Engine.
   */
  namespace Core
  {
    /**
     * @brief Prints information about the Ceremonial Robes Engine.
     */
    void printEngineInfo();
    /**
     * @brief Prints version information about OpenGL, GLEW, and GLFW.
     */
    void printVersionInfo();

    /**
     * @brief Initializes GLFW.
     */
    void initializeGlfw();
    /**
     * @brief Initializes GLEW.
     */
    void initializeGlew();
  }
}

#endif // CRB_CORE_HPP
