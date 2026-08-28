add_library(spatial_hardware STATIC src/device.cpp src/api.cpp)
target_include_directories(spatial_hardware PUBLIC include)
target_link_libraries(spatial_hardware PUBLIC spatial_core)
