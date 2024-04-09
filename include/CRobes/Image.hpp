#ifndef CRB_IMAGE_HPP
#define CRB_IMAGE_HPP

#include <GL/glew.h>
#include <png.h>

#include <stdio.h>
#include <iostream>
#include <string>

namespace crb
{
  /**
   * @brief A namespace containing functions for image loading in the Ceremonial Robes Engine.
   */
  namespace Image
  {
    /**
     * @brief Loads image data from a PNG file.
     * 
     * @param path The file path to the PNG image.
     * @param oData A pointer to the image data buffer where the loaded image data will be stored.
     * @param oWidth A reference to an unsigned integer variable where the width of the loaded image will be stored.
     * @param oHeight A reference to an unsigned integer variable where the height of the loaded image will be stored.
     * @param oHasAlpha A reference to a boolean variable indicating whether the loaded image has an alpha channel.
     * @return true if the image loading was successful, false otherwise.
     */
    bool loadFromPNG(const std::string& path, GLubyte** oData, unsigned int &oWidth, unsigned int &oHeight, bool &oHasAlpha);
  }
}

#endif // CRB_IMAGE_HPP
