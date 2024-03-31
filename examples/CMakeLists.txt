# Executable
add_executable(
  crobes
  Main.cpp
)

# Linking Libraries
target_link_libraries(crobes PUBLIC GL ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})
