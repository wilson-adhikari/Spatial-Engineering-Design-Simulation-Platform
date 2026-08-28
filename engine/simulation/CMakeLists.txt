add_library(spatial_simulation STATIC
  src/solver.cpp
  src/mesh.cpp
  src/physics.cpp
  src/fea.cpp
  src/thermal.cpp
)
target_include_directories(spatial_simulation PUBLIC include)
target_link_libraries(spatial_simulation PUBLIC spatial_math spatial_geometry spatial_core)
