#include "CRobes/Window.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  (void*)window;
  glViewport(0, 0, width, height);
}

void crb::Window::loop()
{
  while (!glfwWindowShouldClose(this->glfwInstance))
  {
    this->_update();
    this->_render();
  }
}

void crb::Window::_initialize()
{
  this->glfwInstance= glfwCreateWindow(
    this->width,
    this->height,
    this->title.c_str(),
    NULL,
    NULL
  );
  if (this->glfwInstance == NULL)
  {
    std::cerr << "Failed to create a GLFW Window!\n";
    glfwTerminate();
  }
  glfwMakeContextCurrent(this->glfwInstance);
  glfwSetFramebufferSizeCallback(this->glfwInstance, framebufferSizeCallback);
  crb::Core::initializeGlew();

  glClearColor(
    this->clearColor.red,
    this->clearColor.green,
    this->clearColor.blue,
    this->clearColor.alpha
  );
}

void crb::Window::_updateDeltaTime()
{
  float currentTime = (float)glfwGetTime();
  this->deltaTime = currentTime - this->lastTime;
  this->lastTime = currentTime;
}

void crb::Window::_updateCursor()
{
  if (this->mouseLocked)
  {
    glfwSetInputMode(this->glfwInstance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return;
  }
  glfwSetInputMode(this->glfwInstance, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void crb::Window::_update()
{
  glfwPollEvents();
  this->_updateDeltaTime();
  this->_updateCursor();
  this->update();
}

void crb::Window::_render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  this->render();
  glfwSwapBuffers(this->glfwInstance);
}
