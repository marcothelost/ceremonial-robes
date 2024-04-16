#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
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
const     std::string  WINDOW_TITLE  {crb::ENGINE_NAME + " " + crb::ENGINE_VERSION};

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
      this->bindCamera(this->camera);
      this->camera.setPosition({8.f, 1.8f, 8.f});

      this->chunks.reserve(9);
      for (int x = 0; x < 3; x++)
      {
        for (int z = 0; z < 3; z++)
        {
          this->chunks.emplace_back(solidFactory.createPlane(
            {(x - 1) * 16.f, 0.f, (z - 1) * 16.f},
            16.f,
            16.f,
            16
          ));
        }
      }
    }

  protected:
    void update()
    {
      const unsigned int bufferWidth = this->getWidth();
      const unsigned int bufferHeight = this->getHeight();
      this->crosshair.setPosition({
        (float)bufferWidth / 2.f - 8.f,
        (float)bufferHeight / 2.f - 8.f
      });

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
      for (const crb::Solids::Solid& chunk : this->chunks)
      {
        chunk.render(this->defaultShader, GL_TRIANGLE_STRIP);
      }
      this->bindShader(this->guiShader);
      this->camera.use2D();
      this->camera.applyMatrix(this->guiShader);
      crosshairTexture.Bind();
      crosshairTexture.ApplyUnit(this->guiShader, 0);
      this->crosshair.render(this->guiShader);
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
    crb::GUI::Element crosshair {
      {0.f, 0.f}, 0.f, 0.f, 16.f, 16.f
    };
    std::vector<crb::Solids::Solid> chunks;

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
