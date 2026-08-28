add_library(spatial_scripting STATIC src/engine.cpp src/bindings.cpp)
target_include_directories(spatial_scripting PUBLIC include)
target_link_libraries(spatial_scripting PUBLIC spatial_core spatial_cad)
