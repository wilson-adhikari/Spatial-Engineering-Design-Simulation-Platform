add_library(spatial_core STATIC
  src/logger.cpp
  src/event.cpp
  src/command.cpp
  src/uuid.cpp
)
target_include_directories(spatial_core PUBLIC include)
target_compile_features(spatial_core PUBLIC cxx_std_20)
