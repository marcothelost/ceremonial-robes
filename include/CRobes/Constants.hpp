#ifndef CRB_CONSTANTS_HPP
#define CRB_CONSTANTS_HPP

#include <string>

namespace crb
{
  /**
   * @brief The name of the Ceremonial Robes Engine.
   */
  inline const std::string ENGINE_NAME {"Ceremonial Robes Engine"};
  /**
   * @brief The version of the Ceremonial Robes Engine.
   */
  inline const std::string ENGINE_VERSION {"0.1 InDev"};
  /**
   * @brief The author of the Ceremonial Robes Engine.
   */
  inline const std::string ENGINE_AUTHOR {"marcothelost"};
  /**
   * @brief The license under which the Ceremonial Robes Engine is distributed.
   */
  inline const std::string ENGINE_LICENSE {"GNU GPLv3"};

  /**
   * @brief The size of the information log buffer.
   */
  inline const unsigned int INFO_LOG_SIZE {512u};
}

#endif // CRB_CONSTANTS_HPP
