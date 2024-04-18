#include "CRobes/Window.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  crb::Window* windowInstance = (crb::Window*)glfwGetWindowUserPointer(window);
  crb::Camera* boundCamera = windowInstance->getBoundCamera();

  windowInstance->setWidth(width);
  windowInstance->setHeight(height);

  if (boundCamera != NULL)
  {
    boundCamera->setBufferWidth(width);
    boundCamera->setBufferHeight(height);
  }

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

void crb::Window::maximize()
{
  int xPos;
  int yPos;
  glfwGetWindowPos(this->glfwInstance, &xPos, &yPos);

  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);

  this->cachedX = xPos;
  this->cachedY = yPos;
  this->cachedWidth = width;
  this->cachedHeight = height;

  glfwSetWindowMonitor(
    this->glfwInstance,
    monitor,
    0,
    0,
    mode->width,
    mode->height,
    mode->refreshRate
  );
  this->maximized = true;
}

void crb::Window::unmaximize()
{
  glfwSetWindowMonitor(
    this->glfwInstance,
    NULL,
    this->cachedX,
    this->cachedY,
    this->cachedWidth,
    this->cachedHeight,
    0
  );
  this->maximized = false;
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
  glfwSetWindowUserPointer(this->glfwInstance, this);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_PRIMITIVE_RESTART);
  crb::Core::initializeGlew();

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPrimitiveRestartIndex(65535);
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

void crb::Window::_updateCamera()
{
  if (this->boundShader == NULL || this->boundCamera == NULL)
  {
    return;
  }
  if (this->mouseLocked)
  {
    std::pair<float, float> mousePosition = crb::Input::getMousePosition(this->glfwInstance);
    this->boundCamera->updatePosition(this->getDeltaTime());
    this->boundCamera->updateRotation(mousePosition);
  }
  this->boundCamera->updateMatrix();
  this->boundCamera->applyMatrix(*this->boundShader);
  this->boundCamera->applyPosition(*this->boundShader);
}

void crb::Window::_updateCursor()
{
  if (!this->mouseLocked)
  {
    glfwSetInputMode(this->glfwInstance, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    return;
  }
  glfwSetInputMode(this->glfwInstance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPos(this->glfwInstance, this->width / 2, this->height / 2);
}

void crb::Window::_update()
{
  glfwPollEvents();
  this->_updateDeltaTime();
  this->_updateCamera();
  this->_updateCursor();
  this->update();
}

void crb::Window::_render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  this->render();
  glfwSwapBuffers(this->glfwInstance);
}
