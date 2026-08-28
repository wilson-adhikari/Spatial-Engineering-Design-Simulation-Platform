add_library(spatial_geometry STATIC
  src/primitives.cpp
  src/curve.cpp
  src/surface.cpp
  src/bbox.cpp
)
target_include_directories(spatial_geometry PUBLIC include)
target_link_libraries(spatial_geometry PUBLIC spatial_math spatial_core)
