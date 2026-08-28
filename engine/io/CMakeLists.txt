add_library(spatial_io STATIC
  src/project.cpp
  src/import_step.cpp
  src/export_stl.cpp
)
target_include_directories(spatial_io PUBLIC include)
target_link_libraries(spatial_io PUBLIC spatial_cad spatial_core)
