#ifndef CRB_GUI_HPP
#define CRB_GUI_HPP

#include "Graphics.hpp"
#include "Space.hpp"

namespace crb
{
  /**
   * @brief Contains classes and utilities related to graphical user interface (GUI) elements in the Ceremonial Robes Engine.
   */
  namespace GUI
  {
    /**
     * @brief A graphical user interface (GUI) element.
     */
    class Element
    {
      public:
        Element(const crb::Space::Vec2& position, const float x, const float y, const float width, const float height);

        /**
         * @brief Sets the position of the element in 2D space.
         * 
         * @param position The new position of the element.
         */
        void setPosition(const crb::Space::Vec2& position)
        { this->position = position; }

        /**
         * @brief Renders the GUI element.
         * 
         * @param shader The shader to use for rendering.
         */
        void render(const crb::Graphics::Shader& shader) const;

      private:
        crb::Graphics::VAO VAO;
        crb::Graphics::VBO VBO;
        crb::Graphics::EBO EBO;

        crb::Space::Vec2 position {0.f};
    };
  }
}

#endif // CRB_GUI_HPP
