#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "CRobes/Constants.hpp"
#include "CRobes/Core.hpp"
#include "CRobes/Color.hpp"
#include "CRobes/Graphics.hpp"
#include "CRobes/Window.hpp"
#include "CRobes/Space.hpp"
#include "CRobes/Camera.hpp"
#include "CRobes/Solids.hpp"
#include "CRobes/GUI.hpp"

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

// Solid Factory
crb::Solids::SolidFactory solidFactory;

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
      GLfloat vertices[] =
      {
        0.f,  0.f,  0.f, 0.f, 0.f,
        16.f, 0.f,  0.f, 1.f, 0.f,
        0.f,  16.f, 0.f, 0.f, 1.f,
        16.f, 16.f, 0.f, 1.f, 1.f,
      };
      GLuint indices[] =
      {
        0, 1, 3,
        0, 3, 2,
      };

      crb::Graphics::VAO VAO;
      crb::Graphics::VBO VBO {vertices, (GLsizeiptr)sizeof(vertices)};
      crb::Graphics::EBO EBO {indices, (GLsizeiptr)sizeof(indices)};

      VAO.Bind();
      VBO.Bind();
      EBO.Bind();

      VAO.LinkAttribute(VBO, 0, 3, GL_FLOAT, 5 * sizeof(GLfloat), (void*)0);
      VAO.LinkAttribute(VBO, 1, 2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

      VAO.Unbind();
      VBO.Unbind();
      EBO.Unbind();

      this->crosshair = new crb::GUI::Element({0.f, 0.f, 0.f}, VAO, VBO, EBO);

      this->bindCamera(this->camera);
      this->camera.setPosition({8.f, 1.8f, 8.f});
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
      this->camera.use3D();
      this->camera.applyMatrix(this->defaultShader);
      soilTexture.Bind();
      soilTexture.ApplyUnit(this->defaultShader, 0);
      this->testSolid.render(this->defaultShader, GL_TRIANGLE_STRIP);
      this->bindShader(this->guiShader);
      this->camera.use2D();
      this->camera.applyMatrix(this->guiShader);
      crosshairTexture.Bind();
      crosshairTexture.ApplyUnit(this->guiShader, 0);
      this->crosshair->render(this->guiShader);
      this->bindShader(this->defaultShader);
    }

  private:
    crb::Graphics::Shader defaultShader
    {
      "resources/Shaders/default.vert",
      "resources/Shaders/default.frag"
    };
    crb::Graphics::Shader guiShader
    {
      "resources/Shaders/gui.vert",
      "resources/Shaders/gui.frag"
    };
    crb::Graphics::Texture soilTexture
    {
      "resources/Textures/soil.png",
      GL_TEXTURE_2D
    };
    crb::Graphics::Texture crosshairTexture
    {
      "resources/Textures/crosshair.png",
      GL_TEXTURE_2D
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
    crb::Solids::Solid testSolid {solidFactory.createPlane(
      {0.f, 0.f, 0.f},
      16.f,
      16.f,
      16
    )};
    crb::GUI::Element* crosshair {NULL};

    bool canFullscreen {true};
};

int main()
{
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
