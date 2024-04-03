#ifndef CRB_SPACE_HPP
#define CRB_SPACE_HPP

#include <cmath>

namespace crb
{
  /**
   * @brief Contains functionalities related to spatial calculations in the Ceremonial Robes Engine.
   */
  namespace Space
  {
    /**
     * @brief The mathematical constant pi.
     */
    const float PI = 3.141593f;

    /**
     * @brief Converts degrees to radians.
     * 
     * @param degrees The angle in degrees.
     * @return The equivalent angle in radians.
     */
    inline float radians(const float degrees)
    { return degrees * crb::Space::PI / 180.f; }

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
        crb::Space::Vec3 operator+(const crb::Space::Vec3& vec) const
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
        crb::Space::Vec3 operator-(const crb::Space::Vec3& vec) const
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
        crb::Space::Vec3 operator*(const T scalar) const
        {
          return
          {
            this->x * scalar,
            this->y * scalar,
            this->z * scalar
          };
        }
        /**
         * @brief Overloaded multiplication operator (scalar * vector).
         * 
         * Multiplies a scalar value by a Vec3 object and returns the result.
         * 
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to multiply by.
         * @param vec The Vec3 object to multiply.
         * @return The resulting Vec3 object.
         */
        template <typename T>
        friend crb::Space::Vec3 operator*(const T scalar, const crb::Space::Vec3& vec)
        {
          return
          {
            vec.x * scalar,
            vec.y * scalar,
            vec.z * scalar
          };
        }
        /**
         * @brief Overloaded addition assignment operator.
         * 
         * Adds a Vec3 object component-wise to this Vec3 object.
         * 
         * @param vec The Vec3 object to add.
         * @return Reference to this Vec3 object after addition.
         */
        crb::Space::Vec3& operator+=(const crb::Space::Vec3& vec)
        {
          this->x += vec.x;
          this->y += vec.y;
          this->z += vec.z;
          return *this;
        }
        /**
         * @brief Overloaded subtraction assignment operator.
         * 
         * Subtracts a Vec3 object component-wise from this Vec3 object.
         * 
         * @param vec The Vec3 object to subtract.
         * @return Reference to this Vec3 object after subtraction.
         */
        crb::Space::Vec3& operator-=(const crb::Space::Vec3& vec)
        {
          this->x += vec.x;
          this->y += vec.y;
          this->z += vec.z;
          return *this;
        }
        /**
         * @brief Overloaded multiplication assignment operator.
         * 
         * Multiplies this Vec3 object by a scalar value.
         * 
         * @param scalar The scalar value to multiply.
         * @return Reference to this Vec3 object after multiplication.
         */
        template <typename T>
        crb::Space::Vec3& operator*=(const T scalar)
        {
          this->x *= scalar;
          this->y *= scalar;
          this->z *= scalar;
          return *this;
        }

        float x {0.f};
        float y {0.f};
        float z {0.f};
    };

    /**
     * @brief Calculates the length of a 3D vector.
     * 
     * @param vec The 3D vector.
     * @return The length of the vector.
     */
    inline float lengthOf(const crb::Space::Vec3& vec)
    { return sqrtf(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)); }
    /**
     * @brief Normalizes a 3D vector.
     * 
     * @param vec The 3D vector to normalize.
     * @return The normalized vector.
     */
    inline crb::Space::Vec3 normalize(const crb::Space::Vec3& vec)
    {
      const float length = crb::Space::lengthOf(vec);
      if (length == 0) return crb::Space::Vec3(0.f);
      return
      {
        vec.x / length,
        vec.y / length,
        vec.z / length,
      };
    }
    /**
     * @brief Computes the dot product of two Vec3 objects.
     * 
     * @param vecOne The first Vec3 object.
     * @param vecTwo The second Vec3 object.
     * @return The dot product of the two Vec3 objects.
     */
    inline float dot(const crb::Space::Vec3& vecOne, const crb::Space::Vec3& vecTwo)
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
              this->elements[y][x] = 0.f;
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
              this->elements[y][x] = x == y ? diagonalValue : 0.f;
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

        /**
         * @brief Multiplies all elements of the matrix by a scalar value.
         * 
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to multiply by.
         * @return The resulting matrix.
         */
        template <typename T>
        crb::Space::Mat4 operator*(const T scalar)
        {
          crb::Space::Mat4 result {*this};
          for (int y = 0; y < 4; y++)
          {
            for (int x = 0; x < 4; x++)
            {
              result[y][x] *= scalar;
            }
          }
          return result;
        }
        /**
         * @brief Multiplies all elements of the matrix by a scalar value (scalar * matrix).
         * 
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to multiply by.
         * @param mat The matrix to multiply.
         * @return The resulting matrix.
         */
        template <typename T>
        friend crb::Space::Mat4 operator*(const T scalar, const crb::Space::Mat4& mat)
        {
          crb::Space::Mat4 result {mat};
          for (int y = 0; y < 4; y++)
          {
            for (int x = 0; x < 4; x++)
            {
              result[y][x] = result[y][x] * scalar;
            }
          }
          return result;
        }
        /**
         * @brief Adds two matrices element-wise.
         * 
         * @param mat The matrix to add.
         * @return The resulting matrix.
         */
        crb::Space::Mat4 operator+(const crb::Space::Mat4& mat)
        {
          crb::Space::Mat4 result {mat};
          for (int y = 0; y < 4; y++)
          {
            for (int x = 0; x < 4; x++)
            {
              result[y][x] = this->elements[y][x] + mat[y][x];
            }
          }
          return result;
        }
        /**
         * @brief Subtracts two matrices element-wise.
         * 
         * @param mat The matrix to subtract.
         * @return The resulting matrix.
         */
        crb::Space::Mat4 operator-(const crb::Space::Mat4& mat)
        {
          crb::Space::Mat4 result {mat};
          for (int y = 0; y < 4; y++)
          {
            for (int x = 0; x < 4; x++)
            {
              result[y][x] = this->elements[y][x] - mat[y][x];
            }
          }
          return result;
        }
        /**
         * @brief Multiplies this matrix by another matrix.
         * 
         * @param mat The matrix to multiply by.
         * @return The resulting matrix.
         */
        crb::Space::Mat4 operator*(const crb::Space::Mat4& mat)
        {
          crb::Space::Mat4 result;
          for (int i = 0; i < 4; i++)
          {
            for (int j = 0; j < 4; j++)
            {
              result[i][j] = 0.f;
              for (int k = 0; k < 4; k++)
              {
                result[i][j] += this->elements[i][k] * mat[k][j];
              }
            }
          }
          return result;
        }

      private:
        float elements[4][4];
    };

    /**
     * @brief Retrieves a pointer to the first element of a matrix for OpenGL usage.
     * 
     * @param mat The matrix.
     * @return A pointer to the first element of the matrix.
     */
    inline const float* valuePointer(const crb::Space::Mat4& mat)
    { return &mat[0][0]; }
    /**
     * @brief Creates a translation matrix.
     * 
     * @param mat The original matrix.
     * @param vec The translation vector.
     * @return The resulting translated matrix.
     */
    inline crb::Space::Mat4 translate(const crb::Space::Mat4&mat, const crb::Space::Vec3& vec)
    {
      crb::Space::Mat4 result {mat};
      result[3][0] = vec.x;
      result[3][1] = vec.y;
      result[3][2] = vec.z;
      return result;
    }
    /**
     * @brief Generates a perspective projection matrix.
     * 
     * @param fov The field of view angle in degrees.
     * @param aspect The aspect ratio of the viewport.
     * @param zNear The distance to the near clipping plane.
     * @param zFar The distance to the far clipping plane.
     * @return The projection matrix.
     */
    crb::Space::Mat4 perspective(const float fov, const float aspect, const float zNear, const float zFar);
    /**
     * @brief Creates a view matrix that simulates a camera looking at a target.
     * 
     * @param eye The position of the camera.
     * @param target The position of the target that the camera is looking at.
     * @param up The up direction of the camera.
     * @return The view matrix.
     */
    crb::Space::Mat4 lookAt(const crb::Space::Vec3& eye, const crb::Space::Vec3& target, const crb::Space::Vec3& up);
  }
}

#endif // CRB_SPACE_HPP
