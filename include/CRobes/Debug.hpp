#ifndef CRB_DEBUG_HPP
#define CRB_DEBUG_HPP

#include <iostream>

#include "Space.hpp"

namespace crb
{
  /**
   * @brief Contains debug functionalities for the Ceremonial Robes Engine.
   */
  namespace Debug
  {
    /**
     * @brief Prints the components of a 3D vector.
     * 
     * @param vec The 3D vector to print.
     */
    void printVec(const crb::Space::Vec3& vec)
    {
      std::cout << "X: " << vec.x << "; Y: " << vec.y << "; Z: " << vec.z << '\n';
    }
  }
}

#endif // CRB_DEBUG_HPP
