# Executable
add_executable(
  crobes
  Main.cpp
)

# Linking Libraries
target_link_libraries(crobes PUBLIC ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${PNG_LIBRARIES} CRobes)
if(WIN32 OR BUILD_FOR_WINDOWS)
  target_link_options(crobes PRIVATE -static -static-libgcc -static-libstdc++)
  target_link_libraries(crobes PUBLIC gdi32 user32 kernel32 opengl32)
else()
  target_link_libraries(crobes PUBLIC GL)
endif()
