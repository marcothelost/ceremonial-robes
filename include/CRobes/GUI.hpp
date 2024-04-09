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
        /**
         * @brief Constructs an Element object with the specified parameters.
         * 
         * @param position The position of the element in 3D space.
         * @param VAO The Vertex Array Object (VAO) of the element.
         * @param VBO The Vertex Buffer Object (VBO) of the element.
         * @param EBO The Element Buffer Object (EBO) of the element.
         */
        Element(const crb::Space::Vec3& position, const crb::Graphics::VAO& VAO, const crb::Graphics::VBO& VBO, const crb::Graphics::EBO& EBO)
        : position(position), VAO(VAO), VBO(VBO), EBO(EBO)
        {}

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

        crb::Space::Vec3 position {0.f};
    };
  }
}

#endif // CRB_GUI_HPP
