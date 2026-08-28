add_library(spatial_math STATIC
  src/vec.cpp
  src/mat.cpp
  src/quat.cpp
  src/transform.cpp
)
target_include_directories(spatial_math PUBLIC include)
target_link_libraries(spatial_math PUBLIC spatial_core)
