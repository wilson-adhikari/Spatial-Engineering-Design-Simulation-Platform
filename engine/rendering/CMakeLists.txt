add_library(spatial_rendering STATIC
  src/renderer.cpp
  src/material.cpp
  src/backend_opengl.cpp
)
target_include_directories(spatial_rendering PUBLIC include)
target_link_libraries(spatial_rendering PUBLIC spatial_scene spatial_core)
