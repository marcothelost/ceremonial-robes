#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "CRobes/Constants.hpp"
#include "CRobes/Core.hpp"
#include "CRobes/Color.hpp"
#include "CRobes/Keys.hpp"
#include "CRobes/File.hpp"
#include "CRobes/Graphics.hpp"
#include "CRobes/Window.hpp"
#include "CRobes/Space.hpp"
#include "CRobes/Camera.hpp"

// Constants
constexpr unsigned int WINDOW_WIDTH  {800u};
constexpr unsigned int WINDOW_HEIGHT {600u};
const     std::string  WINDOW_TITLE  {"GLFW"};

// Camera Settings
constexpr float CAMERA_FOV  {60.f};
constexpr float CAMERA_NEAR {0.1f};
constexpr float CAMERA_FAR  {100.f};

// Vertices and Indices
GLfloat vertices[] =
{
  -0.5f,  -0.5f, -3.f, 1.f, 1.f, 1.f,
   0.0f,  -0.5f, -3.f, 1.f, 1.f, 1.f,
   0.5f,  -0.5f, -3.f, 1.f, 1.f, 1.f,
  -0.25f,  0.0f, -3.f, 1.f, 1.f, 1.f,
   0.25f,  0.0f, -3.f, 1.f, 1.f, 1.f,
   0.0f,   0.5f, -3.f, 1.f, 1.f, 1.f,
};
GLuint indices[] =
{
  0, 1, 3,
  1, 2, 4,
  3, 4, 5,
};

// Window Class
class MainWindow : public crb::Window
{
  public:
    using crb::Window::Window;

    ~MainWindow()
    {
      this->VAO1.Delete();
      this->VBO1.Delete();
      this->EBO1.Delete();
      this->defaultShader.Delete();
    }

    void initialize()
    {
      this->VAO1.Bind();
      this->VBO1.Bind();
      this->EBO1.Bind();

      this->VAO1.LinkAttribute(this->VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
      this->VAO1.LinkAttribute(this->VBO1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

      this->VAO1.Unbind();
      this->VBO1.Unbind();
      this->EBO1.Unbind();
    }

  protected:
    void update()
    {
      std::cout << "FPS: " << this->getFPS() << '\n';
    }

    void render()
    {
      this->defaultShader.Use();
      this->VAO1.Bind();

      camera.updateMatrix();
      camera.applyMatrix(this->defaultShader);

      crb::Space::Mat4 model {1.f};
      defaultShader.SetMatrix4(model, "model");

      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    }

  private:
    crb::Graphics::Shader defaultShader
    {
      "resources/Shaders/default.vert",
      "resources/Shaders/default.frag"
    };
    crb::Camera camera
    {
      CAMERA_FOV,
      WINDOW_WIDTH,
      WINDOW_HEIGHT,
      CAMERA_NEAR,
      CAMERA_FAR
    };

    crb::Graphics::VAO VAO1;
    crb::Graphics::VBO VBO1 {vertices, sizeof(vertices)};
    crb::Graphics::EBO EBO1 {indices, sizeof(indices)};
};

int main()
{
  // Initializing GLFW
  crb::Core::initializeGlfw();

  // Window
  MainWindow window
  {
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE
  };
  window.initialize();
  window.setClearColor(crb::Color::Black);

  // Printing Engine and Version Info
  crb::Core::printEngineInfo();
  std::cout << '\n';
  crb::Core::printVersionInfo();

  // Line Mode
  crb::Graphics::useLineMode();

  // Main Loop
  window.loop();

  // Termination
  glfwTerminate();
  return EXIT_SUCCESS;
}
