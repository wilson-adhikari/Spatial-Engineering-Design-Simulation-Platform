add_library(spatial_scene STATIC
  src/scene.cpp
  src/node.cpp
  src/camera.cpp
  src/mesh.cpp
)
target_include_directories(spatial_scene PUBLIC include)
target_link_libraries(spatial_scene PUBLIC spatial_geometry spatial_core)
