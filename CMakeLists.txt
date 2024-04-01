# CMake Minimum Version
cmake_minimum_required(VERSION 3.5)

# Constants
set(PROJECT_NAME "cerenomialrobes")

# Project Name
project(${PROJECT_NAME})

# C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Finding Library Paths
find_path(GLEW_INCLUDE_DIR NAMES GL/glew.h PATHS ${CMAKE_SOURCE_DIR}/include)
find_path(GLFW_INCLUDE_DIR NAMES GLFW/glfw3.h PATHS ${CMAKE_SOURCE_DIR}/include)

# Finding Libraries
if(WIN32)
  find_library(GLEW_LIBRARY NAMES GLEW.win PATHS ${CMAKE_SOURCE_DIR}/lib)
  find_library(GLFW_LIBRARY NAMES glfw3.win PATHS ${CMAKE_SOURCE_DIR}/lib)
else()
  find_library(GLEW_LIBRARY NAMES GLEW PATHS ${CMAKE_SOURCE_DIR}/lib)
  find_library(GLFW_LIBRARY NAMES glfw3 PATHS ${CMAKE_SOURCE_DIR}/lib)
endif()

# Validating GLEW
if(GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
  message("GLEW found!")
  set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
  set(GLEW_LIBRARIES ${GLEW_LIBRARY})
else()
  message(FATAL_ERROR "GLEW not found!")
endif()

# Validating GLFW
if(GLFW_INCLUDE_DIR AND GLFW_LIBRARY)
  message("GLFW found!")
  set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
  set(GLFW_LIBRARIES ${GLFW_LIBRARY})
else()
  message(FATAL_ERROR "GLFW not found!")
endif()

# Including External Libraries
include_directories(${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

# DLL Files
if(WIN32)
  file(GLOB dll_files ${CMAKE_SOURCE_DIR}/lib/*.dll)
  foreach(dll_file ${dll_files})
    file(COPY ${dll_file} DESTINATION ${CMAKE_SOURCE_DIR}/build/examples)
  endforeach()
endif()

# Subdirectories
add_subdirectory(examples)
