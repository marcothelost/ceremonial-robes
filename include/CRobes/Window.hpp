#ifndef CRB_WINDOW_HPP
#define CRB_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Core.hpp"

namespace crb
{
  /**
   * @class Window
   * @brief Represents an OpenGL window.
   *
   * This class provides functionalities for creating and managing an OpenGL window
   * using GLFW library. It allows setting window size, title, updating the window,
   * rendering content, and handling events.
   */
  class Window
  {
    public:
      /**
       * @brief Constructs a Window object with the specified width, height, and title.
       *
       * @param width The width of the window.
       * @param height The height of the window.
       * @param title The title of the window.
       */
      Window(const unsigned int width, const unsigned int height, const std::string& title)
      : width(width), height(height), title(title)
      { this->_initialize(); }
      /**
       * @brief Destroys the Window object.
       * 
       * This method cleans up resources associated with the window.
       */
      virtual ~Window()
      {
        glfwDestroyWindow(this->glfwInstance);
      }

      /**
       * @brief Runs the main loop of the window.
       */
      void loop();
      /**
       * @brief Closes the window.
       */
      void close()
      { glfwSetWindowShouldClose(this->glfwInstance, GLFW_TRUE); }

      /**
       * @brief Gets the width of the window.
       *
       * @return The width of the window.
       */
      unsigned int getWidth() const
      { return this->width; }
      /**
       * @brief Gets the height of the window.
       *
       * @return The height of the window.
       */
      unsigned int getHeight() const
      { return this->height; }
      /**
       * @brief Gets the title of the window.
       *
       * @return The title of the window.
       */
      std::string getTitle() const
      { return this->title; }

      /**
       * @brief Gets the title of the window.
       *
       * @return The title of the window.
       */
      void setWidth(const unsigned int width)
      { this->width = width; }
      /**
       * @brief Sets the height of the window.
       *
       * @param height The new height of the window.
       */
      void setHeight(const unsigned int height)
      { this->height = height; }
      /**
       * @brief Sets the title of the window.
       *
       * @param title The new title of the window.
       */
      void setTitle(const std::string& title)
      {
        this->title = title;
        glfwSetWindowTitle(this->glfwInstance, title.c_str());
      }

    protected:
      /**
       * @brief Updates the window content.
       *
       * Override this method to implement custom update behavior.
       */
      virtual void update()
      {}
      /**
       * @brief Renders the window content.
       *
       * Override this method to implement custom rendering behavior.
       */
      virtual void render()
      {}

    private:
      unsigned int width  {800u};
      unsigned int height {600u};
      std::string title   {"GLFW"};

      GLFWwindow* glfwInstance {NULL};

      /**
       * @brief Internal method for initializing the window.
       */
      void _initialize();
      /**
       * @brief Internal method for updating the window content.
       */
      void _update();
      /**
       * @brief Internal method for rendering the window content.
       */
      void _render();
  };
}

#endif // CRB_WINDOW_HPP
