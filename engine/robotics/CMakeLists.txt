add_library(spatial_robotics STATIC
  src/kinematics.cpp
  src/dynamics.cpp
  src/trajectory.cpp
)
target_include_directories(spatial_robotics PUBLIC include)
target_link_libraries(spatial_robotics PUBLIC spatial_math spatial_cad spatial_core)
