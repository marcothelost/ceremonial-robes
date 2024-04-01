#ifndef CRB_FILE_HPP
#define CRB_FILE_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

namespace crb
{
  /**
   * @brief Contains functions related to file operations in the Ceremonial Robes Engine.
   */
  namespace File
  {
    /**
     * @brief Reads the contents of a file specified by the given path.
     *
     * @param path The path to the file.
     * @return The contents of the file as a string.
     */
    std::string getContents(const std::string& path);
  }
}

#endif // CRB_FILE_HPP
