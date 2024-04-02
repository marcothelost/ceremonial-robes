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
    inline void printVector(const crb::Space::Vec3& vec)
    {
      std::cout << "X: " << vec.x << "; Y: " << vec.y << "; Z: " << vec.z << '\n';
    }
    /**
     * @brief Prints the elements of a 4x4 matrix.
     * 
     * @param mat The 4x4 matrix to print.
     */
    inline void printMatrix(const crb::Space::Mat4& mat)
    {
      for (int y = 0; y < 4; y++)
      {
        for (int x = 0; x < 4; x++)
        {
          std::cout << mat[y][x] << " ";
        }
        std::cout << '\n';
      }
    }
  }
}

#endif // CRB_DEBUG_HPP
