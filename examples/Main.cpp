#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <string>

// Constants
constexpr unsigned int WINDOW_WIDTH  {800u};
constexpr unsigned int WINDOW_HEIGHT {600u};
const     std::string  WINDOW_TITLE  {"GLFW"};

int main()
{
  // Initializing GLFW
  GLenum glfwInitializationState = glfwInit();
  if (!glfwInitializationState)
  {
    std::cerr << "Failed to initialize GLFW!\n";
    return EXIT_FAILURE;
  }

  // Window Hints
  glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Creating a GLFW Window
  GLFWwindow* window = glfwCreateWindow(
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE.c_str(),
    NULL,
    NULL
  );
  if (window == NULL)
  {
    std::cerr << "Failed to create a GLFW Window!\n";
    glfwTerminate();
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(window);

  // Initializing GLEW
  GLenum glewInitializationState = glewInit();
  if (glewInitializationState != GLEW_OK)
  {
    std::cerr << "Failed to initialize GLEW!\n";
    std::cerr << "Error: " << glewGetErrorString(glewInitializationState) << '\n';
    glfwTerminate();
    return EXIT_FAILURE;
  }

  // Clear Color
  GLclampf red   {0.f};
  GLclampf green {0.f};
  GLclampf blue  {0.f};
  GLclampf alpha {1.f};
  glClearColor(red, green, blue, alpha);

  // Main Loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
  }

  // Termination
  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}
