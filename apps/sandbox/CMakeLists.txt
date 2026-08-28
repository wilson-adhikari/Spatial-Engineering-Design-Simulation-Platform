add_executable(spatial_sandbox src/main.cpp)
target_link_libraries(spatial_sandbox PRIVATE spatial_core spatial_scene spatial_rendering spatial_simulation)
target_include_directories(spatial_sandbox PRIVATE ../../engine/simulation/include)

