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

        /**
         * @brief Overloaded addition operator.
         * 
         * Adds two Vec3 objects component-wise and returns the result.
         * 
         * @param vec The Vec3 object to add.
         * @return The resulting Vec3 object.
         */
        crb::Space::Vec3 operator+(const crb::Space::Vec3& vec)
        {
          return
          {
            this->x + vec.x,
            this->y + vec.y,
            this->z + vec.z
          };
        }
        /**
         * @brief Overloaded subtraction operator.
         * 
         * Subtracts two Vec3 objects component-wise and returns the result.
         * 
         * @param vec The Vec3 object to subtract.
         * @return The resulting Vec3 object.
         */
        crb::Space::Vec3 operator-(const crb::Space::Vec3& vec)
        {
          return
          {
            this->x - vec.x,
            this->y - vec.y,
            this->z - vec.z
          };
        }
        /**
         * @brief Overloaded multiplication operator.
         * 
         * Multiplies a Vec3 object by a scalar value and returns the result.
         * 
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to multiply by.
         * @return The resulting Vec3 object.
         */
        template <typename T>
        crb::Space::Vec3 operator*(const T scalar)
        {
          return
          {
            this->x * scalar,
            this->y * scalar,
            this->z * scalar
          };
        }

        float x {0.f};
        float y {0.f};
        float z {0.f};
    };

    /**
     * @brief Computes the dot product of two Vec3 objects.
     * 
     * @param vecOne The first Vec3 object.
     * @param vecTwo The second Vec3 object.
     * @return The dot product of the two Vec3 objects.
     */
    inline float dot(const crb::Space::Vec3& vecOne, crb::Space::Vec3& vecTwo)
    { return vecOne.x * vecTwo.x + vecOne.y * vecTwo.y + vecOne.z * vecTwo.z; }
    /**
     * @brief Computes the cross product of two Vec3 objects.
     * 
     * @param vecOne The first Vec3 object.
     * @param vecTwo The second Vec3 object.
     * @return The cross product of the two Vec3 objects.
     */
    inline crb::Space::Vec3 cross(const crb::Space::Vec3& vecOne, crb::Space::Vec3& vecTwo)
    {
      return
      {
        vecOne.y * vecTwo.z - vecOne.z * vecTwo.y,
        vecOne.z * vecTwo.x - vecOne.x * vecTwo.z,
        vecOne.x * vecTwo.y - vecOne.y * vecTwo.x
      };
    }

    /**
     * @brief Represents a 4x4 matrix.
     * 
     * This class represents a 4x4 matrix used for transformations in 3D graphics.
     */
    class Mat4
    {
      public:
        /**
         * @brief Default constructor.
         */
        Mat4()
        {
          for (int y = 0; y < 4; y++)
          {
            for (int x = 0; x < 4; x++)
            {
              elements[y][x] = 0.f;
            }
          }
        }
        /**
         * @brief Constructs a Mat4 object with the specified diagonal value.
         * 
         * @param diagonalValue The value to set for the diagonal elements.
         */
        Mat4(const float diagonalValue)
        {
          for (int y = 0; y < 4; y++)
          {
            for (int x = 0; x < 4; x++)
            {
              elements[y][x] = x == y ? diagonalValue : 0.f;
            }
          }
        }

        /**
         * @brief Accesses the specified row of the matrix.
         * 
         * @param index The index of the row to access.
         * @return A pointer to the specified row.
         */
        float* operator[](int index)
        {
          return this->elements[index];
        }
        /**
         * @brief Accesses the specified row of the matrix (const version).
         * 
         * @param index The index of the row to access.
         * @return A pointer to the specified row.
         */
        const float* operator[](int index) const
        {
          return this->elements[index];
        }

      private:
        float elements[4][4];
    };
  }
}

#endif // CRB_SPACE_HPP
