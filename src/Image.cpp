#include "CRobes/Image.hpp"

bool crb::Image::loadFromPNG(const std::string& path, GLubyte** oData, unsigned int &oWidth, unsigned int &oHeight, bool &oHasAlpha)
{
  FILE* file = fopen(path.c_str(), "rb");
  if (!file)
  {
    std::cerr << "Failed to open the image (" << path << ")!\n";
    return false;
  }

  png_structp pngPointer = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!pngPointer)
  {
    std::cerr << "Failed to create a read struct!\n";
    fclose(file);
    return false;
  }

  png_infop pngInfoPointer = png_create_info_struct(pngPointer);
  if (!pngInfoPointer)
  {
    std::cerr << "Failed to create an info struct!\n";
    png_destroy_read_struct(&pngPointer, NULL, NULL);
    fclose(file);
    return false;
  }

  if (setjmp(png_jmpbuf(pngPointer)))
  {
    png_destroy_read_struct(&pngPointer, NULL, NULL);
    fclose(file);
    return false;
  }

  png_init_io(pngPointer, file);
  png_read_info(pngPointer, pngInfoPointer);

  oWidth = png_get_image_width(pngPointer, pngInfoPointer);
  oHeight = png_get_image_height(pngPointer, pngInfoPointer);
  png_byte colorType = png_get_color_type(pngPointer, pngInfoPointer);
  png_byte bitDepth = png_get_bit_depth(pngPointer, pngInfoPointer);

  if (colorType == PNG_COLOR_TYPE_PALETTE)
  {
    png_set_palette_to_rgb(pngPointer);
  }
  else if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
  {
    png_set_expand_gray_1_2_4_to_8(pngPointer);
  }
  if (png_get_valid(pngPointer, pngInfoPointer, PNG_INFO_tRNS))
  {
    png_set_tRNS_to_alpha(pngPointer);
  }
  if (bitDepth == 16)
  {
    png_set_strip_16(pngPointer);
  }
  if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
  {
    png_set_gray_to_rgb(pngPointer);
  }

  png_read_update_info(pngPointer, pngInfoPointer);

  *oData = (GLubyte*)malloc(png_get_rowbytes(pngPointer, pngInfoPointer) * oHeight);
  if (!*oData)
  {
    std::cerr << "Failed to allocate output data for image!\n";
    png_destroy_read_struct(&pngPointer, NULL, NULL);
    fclose(file);
    return false;
  }

  png_bytep* rowPointers = (png_bytep*)malloc(sizeof(png_bytep) * oHeight);
  for (int y = 0; y < oHeight; y++)
  {
    rowPointers[y] = *oData + y * png_get_rowbytes(pngPointer, pngInfoPointer);
  }

  png_read_image(pngPointer, rowPointers);
  png_free(pngPointer, rowPointers);
  png_destroy_read_struct(&pngPointer, NULL, NULL);

  oHasAlpha = (colorType & PNG_COLOR_MASK_ALPHA) != 0;

  fclose(file);
  return true;
}
