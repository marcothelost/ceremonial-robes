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

void crb::Core::initializeGlfw()
{
  GLenum glfwInitializationState = glfwInit();
  if (!glfwInitializationState)
  {
    std::cerr << "Failed to initialize GLFW!\n";
  }
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void crb::Core::initializeGlew()
{
  GLenum glewInitializationState = glewInit();
  if (glewInitializationState != GLEW_OK)
  {
    std::cerr << "Failed to initialize GLEW!\n";
    std::cerr << "Error: " << glewGetErrorString(glewInitializationState) << '\n';
  }
}
