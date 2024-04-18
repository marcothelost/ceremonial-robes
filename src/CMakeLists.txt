# Library
add_library(
  CRobes
  Core.cpp
  File.cpp
  Image.cpp
  Graphics.cpp
  Window.cpp
  Space.cpp
  Camera.cpp
  Solids.cpp
  GUI.cpp
)

# Linking Libraries
target_link_libraries(CRobes PUBLIC ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${PNG_LIBRARIES})
