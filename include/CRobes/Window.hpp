#ifndef CRB_WINDOW_HPP
#define CRB_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <string>

#include "Core.hpp"
#include "Color.hpp"
#include "Input.hpp"
#include "Camera.hpp"

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
       * @brief Gets the clear color used for rendering.
       * 
       * @return The clear color used for rendering.
       */
      crb::Color::RGBA getClearColor() const
      { return this->clearColor; }
      /**
       * @brief Gets the time difference between frames.
       * 
       * @return The time difference between frames.
       */
      float getDeltaTime() const
      { return this->deltaTime; }
      /**
       * @brief Calculates and returns the frames per second (FPS).
       * 
       * @return The frames per second (FPS), rounded to the nearest integer.
       */
      int getFPS() const
      { return round(1.f / this->deltaTime); }
      /**
       * @brief Gets the currently bound shader.
       * 
       * @return A pointer to the currently bound shader.
       */
      crb::Graphics::Shader* getBoundShader() const
      { return this->boundShader; }
      /**
       * @brief Gets the currently bound camera.
       * 
       * @return A pointer to the currently bound camera.
       */
      crb::Camera* getBoundCamera() const
      { return this->boundCamera; }
      /**
       * @brief Checks if the mouse is locked.
       * 
       * @return True if the mouse is locked, false otherwise.
       */
      bool getMouseLocked() const
      { return this->mouseLocked; }
      /**
       * @brief Checks if the window is currently maximized.
       * 
       * @return True if the window is maximized, false otherwise.
       */
      bool getMaximized() const
      { return this->maximized; }

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
      /**
       * @brief Sets the clear color used for rendering.
       * 
       * @param clearColor The new clear color.
       */
      void setClearColor(const crb::Color::RGBA& clearColor)
      {
        this->clearColor = clearColor;
        glClearColor(
          this->clearColor.red,
          this->clearColor.green,
          this->clearColor.blue,
          this->clearColor.alpha
        );
      }
      /**
       * @brief Sets the mouse lock state.
       * 
       * @param state The state to set the mouse lock to.
       */
      void setMouseLocked(const bool state)
      { this->mouseLocked = state; }

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
       * @brief Maximizes the window.
       */
      void maximize();
      /**
       * @brief Restores the window to its original size after being maximized.
       */
      void unmaximize();

      /**
       * @brief Checks if a key is currently pressed.
       * 
       * @param key The key to check.
       * @return True if the key is pressed, false otherwise.
       */
      inline bool isKeyPressed(const crb::Key& key)
      { return crb::Input::isKeyPressed(this->glfwInstance, key); }

      /**
       * @brief Binds a shader for rendering.
       * 
       * @param shader The shader to bind.
       */
      void bindShader(crb::Graphics::Shader& shader)
      { this->boundShader = &shader; shader.Use(); }
      /**
       * @brief Binds a camera for rendering.
       * 
       * @param camera The camera to bind.
       */
      void bindCamera(crb::Camera& camera)
      {
        this->boundCamera = &camera;
        this->boundCamera->setBufferWidth(this->width);
        this->boundCamera->setBufferHeight(this->height);
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

      unsigned int cachedX      {0u};
      unsigned int cachedY      {0u};
      unsigned int cachedWidth  {800u};
      unsigned int cachedHeight {600u};

      GLFWwindow*      glfwInstance {NULL};
      crb::Color::RGBA clearColor   {crb::Color::Black};

      crb::Graphics::Shader* boundShader {NULL};
      crb::Camera*           boundCamera {NULL};

      float deltaTime {0.f};
      float lastTime  {(float)glfwGetTime()};

      bool mouseLocked {false};
      bool maximized   {false};

      /**
       * @brief Internal method for initializing the window.
       */
      void _initialize();
      /**
       * @brief Internal method for updating the time difference between frames.
       */
      void _updateDeltaTime();
      /**
       * @brief Internal method for updating the camera.
       */
      void _updateCamera();
      /**
       * @brief Internal method for updating the cursor.
       */
      void _updateCursor();
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
