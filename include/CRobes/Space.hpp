#ifndef CRB_SPACE_HPP
#define CRB_SPACE_HPP

namespace crb
{
  /**
   * @brief Contains functionalities related to spatial calculations in the Ceremonial Robes Engine.
   */
  namespace Space
  {
    /**
     * @class Vec3
     * @brief Represents a 3D vector.
     * 
     * This class represents a 3D vector in space with x, y, and z components.
     */
    class Vec3
    {
      public:
        /**
         * @brief Constructs a Vec3 object with the specified x, y, and z components.
         * 
         * @param x The x component of the vector.
         * @param y The y component of the vector.
         * @param z The z component of the vector.
         */
        Vec3(const float x, const float y, const float z)
        : x(x), y(y), z(z)
        {}
        /**
         * @brief Default constructor.
         * 
         * Initializes the vector to (0, 0, 0).
         */
        Vec3()
        {}
        /**
         * @brief Constructs a Vec3 object with all components set to the same scalar value.
         * 
         * @param scalar The scalar value to set for all components.
         */
        Vec3(const float scalar)
        : x(scalar), y(scalar), z(scalar)
        {}

        float x {0.f};
        float y {0.f};
        float z {0.f};
    };
  }
}

#endif // CRB_SPACE_HPP
