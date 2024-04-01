#ifndef CRB_COLOR_HPP
#define CRB_COLOR_HPP

#include <stdint.h>

namespace crb
{
  /**
   * @brief Contains functionalities related to colors in the Ceremonial Robes Engine.
   */
  namespace Color
  {
    /**
     * @brief Represents a color in RGBA format.
     */
    struct RGBA
    {
      float red;
      float green;
      float blue;
      float alpha;

      /**
       * @brief Constructs an RGBA color with the specified red, green, blue, and alpha values.
       * 
       * @param red The red component value (0 to 255).
       * @param green The green component value (0 to 255).
       * @param blue The blue component value (0 to 255).
       * @param alpha The alpha (opacity) component value (0.0 to 1.0).
       */
      RGBA(const uint8_t red, const uint8_t green, const uint8_t blue, const float alpha)
      : red(red / 255.f), green(green / 255.f), blue(blue / 255.f), alpha(alpha)
      {}
    };

    /**
     * @brief Predefined RGBA color constant for black.
     */
    inline const crb::Color::RGBA Black {0, 0, 0, 1.f};
    /**
     * @brief Predefined RGBA color constant for white.
     */
    inline const crb::Color::RGBA White {255, 255, 255, 1.f};
    /**
     * @brief Predefined RGBA color constant for red.
     */
    inline const crb::Color::RGBA Red {255, 0, 0, 1.f};
    /**
     * @brief Predefined RGBA color constant for green.
     */
    inline const crb::Color::RGBA Green {0, 255, 0, 1.f};
    /**
     * @brief Predefined RGBA color constant for blue.
     */
    inline const crb::Color::RGBA Blue {0, 0, 255, 1.f};
    /**
     * @brief Predefined RGBA color constant for yellow.
     */
    inline const crb::Color::RGBA Yellow {255, 255, 0, 1.f};
    /**
     * @brief Predefined RGBA color constant for cyan.
     */
    inline const crb::Color::RGBA Cyan {255, 255, 0, 1.f};
    /**
     * @brief Predefined RGBA color constant for magenta.
     */
    inline const crb::Color::RGBA Magenta {255, 0, 255, 1.f};
  }
}

#endif // CRB_COLOR_HPP
