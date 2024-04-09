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
find_path(PNG_INCLUDE_DIR NAMES libpng16/png.h PATHS ${CMAKE_SOURCE_DIR}/include)
set(CROBES_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Finding Libraries
if(WIN32)
  find_library(GLEW_LIBRARY NAMES GLEW.win PATHS ${CMAKE_SOURCE_DIR}/lib)
  find_library(GLFW_LIBRARY NAMES glfw3.win PATHS ${CMAKE_SOURCE_DIR}/lib)
  find_library(PNG_LIBRARY NAMES png16.win PATHS ${CMAKE_SOURCE_DIR}/lib)
else()
  find_library(GLEW_LIBRARY NAMES GLEW PATHS ${CMAKE_SOURCE_DIR}/lib)
  find_library(GLFW_LIBRARY NAMES glfw3 PATHS ${CMAKE_SOURCE_DIR}/lib)
  find_library(PNG_LIBRARY NAMES png16 PATHS ${CMAKE_SOURCE_DIR}/lib)
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

# Validating PNG
if(PNG_INCLUDE_DIR AND PNG_LIBRARY)
  message("PNG found!")
  set(PNG_INCLUDE_DIRS ${PNG_INCLUDE_DIR})
  set(PNG_LIBRARIES ${PNG_LIBRARY})
else()
  message(FATAL_ERROR "PNG not found!")
endif()

# Validating Ceremonial Robes
if(EXISTS ${CROBES_INCLUDE_DIR})
  message("Ceremonial Robes found!")
  set(CROBES_INCLUDE_DIRS ${CROBES_INCLUDE_DIR})
else()
  message(FATAL_ERROR "Ceremonial Robes not found!")
endif()

# Including External Libraries
include_directories(${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS} ${CROBES_INCLUDE_DIRS})

# DLL Files
if(WIN32)
  file(GLOB dll_files ${CMAKE_SOURCE_DIR}/lib/*.dll)
  foreach(dll_file ${dll_files})
    file(COPY ${dll_file} DESTINATION ${CMAKE_SOURCE_DIR}/build/examples)
  endforeach()
endif()

# Resource Files
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_SOURCE_DIR}/build/examples)

# Subdirectories
add_subdirectory(src)
add_subdirectory(examples)
