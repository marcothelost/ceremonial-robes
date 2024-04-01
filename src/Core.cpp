#include "CRobes/Core.hpp"

void crb::Core::printEngineInfo()
{
  std::cout << crb::ENGINE_NAME << " " << crb::ENGINE_VERSION << '\n';
  std::cout << "Created by " << crb::ENGINE_AUTHOR << '\n';
  std::cout << "Licensed under " << crb::ENGINE_LICENSE << '\n';
}

void crb::Core::printVersionInfo()
{
  std::cout << "OpenGL: " << glGetString(GL_VERSION) << '\n';
  std::cout << "GLEW:   " << glewGetString(GLEW_VERSION) << '\n';
  std::cout << "GLFW:   " << glfwGetVersionString() << '\n';
}
