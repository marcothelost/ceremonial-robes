#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "CRobes/Constants.hpp"
#include "CRobes/Core.hpp"
#include "CRobes/Color.hpp"
#include "CRobes/File.hpp"
#include "CRobes/Graphics.hpp"
#include "CRobes/Window.hpp"
#include "CRobes/Space.hpp"
#include "CRobes/Camera.hpp"
#include "CRobes/Solids.hpp"

#include "Noise.hpp"

// Constants
constexpr unsigned int WINDOW_WIDTH  {800u};
constexpr unsigned int WINDOW_HEIGHT {600u};
const     std::string  WINDOW_TITLE  {"GLFW"};

// Camera Settings
constexpr float CAMERA_FOV         {60.f};
constexpr float CAMERA_NEAR        {0.1f};
constexpr float CAMERA_FAR         {100.f};
constexpr float CAMERA_SPEED       {5.f};
constexpr float CAMERA_SENSITIVITY {0.1};

const unsigned int segmentCount = 128;

// Window Class
class MainWindow : public crb::Window
{
  public:
    using crb::Window::Window;

    ~MainWindow()
    {
      this->defaultShader.Delete();
    }

    void initialize()
    {
      GLfloat vertices[(segmentCount + 1) * (segmentCount + 1) * 6] {0.f};
      GLuint indices[(segmentCount * 2 + 3) * segmentCount] {0};

      const siv::PerlinNoise perlin{123u};

      for (int z = 0; z < segmentCount + 1; z++)
      {
        for (int x = 0; x < segmentCount + 1; x++)
        {
          int index = z * (segmentCount + 1) * 6 + x * 6;
          float n = perlin.octave2D_01(x * 0.03f, z * 0.03f, 24);

          vertices[index]     = x * 0.5f;
          vertices[index + 1] = n * 25.f;
          vertices[index + 2] = z * 0.5f;
          vertices[index + 3] = 0.8f - n * 0.7f;
          vertices[index + 4] = 0.8f - n * 0.7f;
          vertices[index + 5] = 0.8f - n * 0.7f;
        }
      }

      for (int i = 0; i < segmentCount; i++)
      {
        for (int j = 0; j <= segmentCount * 2 + 2; j++)
        {
          if (j == segmentCount * 2 + 2)
          {
            indices[i * (segmentCount * 2 + 2) + j + i] = 65535;
            continue;
          }
          indices[i * (segmentCount * 2 + 2) + j + i] =
             i * (segmentCount + 1)
             + (j % 2 == 0 ? j : j + segmentCount)
             - j / 2;
        }
      }

      glEnable(GL_CULL_FACE);
      glEnable(GL_PRIMITIVE_RESTART);
      glCullFace(GL_BACK);
      glPrimitiveRestartIndex(65535);

      crb::Graphics::VAO VAO1;
      crb::Graphics::VBO VBO1 {vertices, sizeof(vertices)};
      crb::Graphics::EBO EBO1 {indices, sizeof(indices)};

      VAO1.Bind();
      VBO1.Bind();
      EBO1.Bind();

      VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
      VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

      VAO1.Unbind();
      VBO1.Unbind();
      EBO1.Unbind();

      this->testSolid = new crb::Solids::Solid(
        {0.f, 0.f, 0.f},
        VAO1,
        VBO1,
        EBO1,
        (segmentCount * 2 + 3) * segmentCount
      );
      this->bindCamera(this->camera);
    }

  protected:
    void update()
    {
      if (this->isKeyPressed(crb::Key::E))
      { this->setMouseLocked(true); }
      if (this->isKeyPressed(crb::Key::Escape))
      { this->setMouseLocked(false); }

      if (this->isKeyPressed(crb::Key::F))
      {
        if (!this->canFullscreen) return;
        this->getMaximized()
          ? this->unmaximize()
          : this->maximize();
        this->canFullscreen = false;
      }
      else
      {
        this->canFullscreen = true;
      }

      if (!this->getMouseLocked()) return;

      if (this->isKeyPressed(crb::Key::C))
      { crb::Graphics::usePointMode(); }
      else if (this->isKeyPressed(crb::Key::V))
      { crb::Graphics::useLineMode(); }
      else if (this->isKeyPressed(crb::Key::B))
      { crb::Graphics::useFillMode(); }

      float xFactor {0.f};
      float yFactor {0.f};
      float zFactor {0.f};

      if (this->isKeyPressed(crb::Key::W))
      { zFactor += 1.f; }
      if (this->isKeyPressed(crb::Key::S))
      { zFactor -= 1.f; }
      if (this->isKeyPressed(crb::Key::Spacebar))
      { yFactor += 1.f; }
      if (this->isKeyPressed(crb::Key::LeftShift))
      { yFactor -= 1.f; }
      if (this->isKeyPressed(crb::Key::A))
      { xFactor += 1.f; }
      if (this->isKeyPressed(crb::Key::D))
      { xFactor -= 1.f; }

      if (this->isKeyPressed(crb::Key::Num1))
      { this->camera.setFov(40.f); }
      if (this->isKeyPressed(crb::Key::Num2))
      { this->camera.setFov(60.f); }
      if (this->isKeyPressed(crb::Key::Num3))
      { this->camera.setFov(80.f); }
      if (this->isKeyPressed(crb::Key::Num4))
      { this->camera.setFov(100.f); }
      if (this->isKeyPressed(crb::Key::Num5))
      { this->camera.setFov(120.f); }

      this->camera.setMovement({
        xFactor,
        yFactor,
        zFactor
      });
    }

    void render()
    {
      this->bindShader(this->defaultShader);
      this->testSolid->render(this->defaultShader, GL_TRIANGLE_STRIP);
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
      CAMERA_FAR,
      CAMERA_SPEED,
      CAMERA_SENSITIVITY
    };
    crb::Solids::Solid* testSolid {NULL};

    bool canFullscreen {true};
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
  window.setClearColor({220, 220, 220, 1.f});

  // Printing Engine and Version Info
  crb::Core::printEngineInfo();
  std::cout << '\n';
  crb::Core::printVersionInfo();

  // Line Mode and Settings
  crb::Graphics::useLineMode();
  crb::Graphics::setPointSize(5.f);

  // Main Loop
  window.loop();

  // Termination
  glfwTerminate();
  return EXIT_SUCCESS;
}
