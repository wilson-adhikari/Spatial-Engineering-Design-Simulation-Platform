add_library(spatial_vision STATIC src/tracking.cpp src/camera.cpp)
target_include_directories(spatial_vision PUBLIC include)
target_link_libraries(spatial_vision PUBLIC spatial_core spatial_math)
