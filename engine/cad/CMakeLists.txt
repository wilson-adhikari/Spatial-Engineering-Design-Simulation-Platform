add_library(spatial_cad STATIC
  src/part.cpp
  src/sketch.cpp
  src/sketch_solver.cpp
  src/feature.cpp
  src/primitives.cpp
  src/assembly.cpp
)
target_include_directories(spatial_cad PUBLIC include)
target_link_libraries(spatial_cad PUBLIC spatial_geometry spatial_scene spatial_core)
