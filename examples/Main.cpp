#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "CRobes/Constants.hpp"
#include "CRobes/Core.hpp"
#include "CRobes/File.hpp"
#include "CRobes/Graphics.hpp"
#include "CRobes/Window.hpp"

// Constants
constexpr unsigned int WINDOW_WIDTH  {800u};
constexpr unsigned int WINDOW_HEIGHT {600u};
const     std::string  WINDOW_TITLE  {"GLFW"};

// Vertices and Indices
GLfloat vertices[] =
{
  -0.5f,  -0.5f, 0.f, 1.f, 1.f, 1.f,
   0.0f,  -0.5f, 0.f, 1.f, 1.f, 1.f,
   0.5f,  -0.5f, 0.f, 1.f, 1.f, 1.f,
  -0.25f,  0.0f, 0.f, 1.f, 1.f, 1.f,
   0.25f,  0.0f, 0.f, 1.f, 1.f, 1.f,
   0.0f,   0.5f, 0.f, 1.f, 1.f, 1.f,
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
    void render()
    {
      this->defaultShader.Use();
      this->VAO1.Bind();
      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    }

  private:
    crb::Graphics::Shader defaultShader
    {
      "resources/Shaders/default.vert",
      "resources/Shaders/default.frag"
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

  // Clear Color
  GLclampf red   {0.f};
  GLclampf green {0.f};
  GLclampf blue  {0.f};
  GLclampf alpha {1.f};
  glClearColor(red, green, blue, alpha);

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
