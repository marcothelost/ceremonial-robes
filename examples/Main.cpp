#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
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
#include "CRobes/Debug.hpp"

// Window Settings
constexpr unsigned int WINDOW_WIDTH  {800u};
constexpr unsigned int WINDOW_HEIGHT {600u};
const     std::string  WINDOW_TITLE  {crb::ENGINE_NAME + " " + crb::ENGINE_VERSION};

// Camera Settings
constexpr float CAMERA_FOV         {60.f};
constexpr float CAMERA_NEAR        {0.1f};
constexpr float CAMERA_FAR         {512.f};
constexpr float CAMERA_SPEED       {5.f};
constexpr float CAMERA_SENSITIVITY {0.1};

// Settings
constexpr unsigned int RENDER_DISTANCE {8};

// Camera Position
const crb::Space::Vec3 defaultCameraPosition {8.f, 1.8f, 8.f};

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
      this->camera.setPosition(defaultCameraPosition);
      this->chunks.reserve(pow(RENDER_DISTANCE * 2 - 1, 2));

      for (int z = 0; z < 3; z++)
      {
        for (int x = 0; x < 3; x++)
        {
          this->chunks.emplace_back(solidFactory.createPlane(
            {(x - 1) * crb::CHUNK_SIZE, 0.f, (z - 1) * crb::CHUNK_SIZE},
            crb::CHUNK_SIZE,
            crb::CHUNK_SIZE,
            crb::CHUNK_SEGMENTS
          ));
        }
      }
    }

  protected:
    std::vector<std::pair<int, int>> calculateRequiredChunks()
    {
      std::vector<std::pair<int, int>> chunks;

      int cameraChunkX = crb::Space::getChunkX(this->camera.getPosition());
      int cameraChunkZ = crb::Space::getChunkZ(this->camera.getPosition());

      for (int z = 0; z < RENDER_DISTANCE * 2 - 1; z++)
      {
        for (int x = 0; x < RENDER_DISTANCE * 2 - 1; x++)
        {
          chunks.push_back(std::pair(
            x - RENDER_DISTANCE + cameraChunkX + 1,
            z - RENDER_DISTANCE + cameraChunkZ + 1
          ));
        }
      }

      return chunks;
    }

    void updateChunks()
    {
      std::vector<std::pair<int, int>> requiredChunks = this->calculateRequiredChunks();

      this->chunks.erase(std::remove_if(
        this->chunks.begin(),
        this->chunks.end(),
        [&](const crb::Solids::Solid& chunk)
        {
          for (const auto& chunkPosition : requiredChunks)
          {
            if (
              crb::Space::getChunkX(chunk.getPosition().x) == chunkPosition.first &&
              crb::Space::getChunkZ(chunk.getPosition().z) == chunkPosition.second
            ) return false;
          }
          return true;
        }
      ), this->chunks.end());

      for (const auto& chunkPosition : requiredChunks)
      {
        bool chunkFound {false};
        for (const auto& chunk : this->chunks)
        {
          if (
            crb::Space::getChunkX(chunk.getPosition().x) == chunkPosition.first &&
            crb::Space::getChunkZ(chunk.getPosition().z) == chunkPosition.second
          ) chunkFound = true;
        }
        if (!chunkFound)
        {
          this->chunks.emplace_back(solidFactory.createPlane(
            {chunkPosition.first * crb::CHUNK_SIZE, 0.f, chunkPosition.second * crb::CHUNK_SIZE},
            crb::CHUNK_SIZE,
            crb::CHUNK_SIZE,
            crb::CHUNK_SEGMENTS
          ));
        }
      }
    }

    void update()
    {
      this->updateChunks();

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

      if (this->isMouseButtonPressed(crb::MouseButton::LeftButton))
      {
        this->camera.setSpeed(CAMERA_SPEED * 5.f);
      }
      else
      {
        this->camera.setSpeed(CAMERA_SPEED);
      }

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
