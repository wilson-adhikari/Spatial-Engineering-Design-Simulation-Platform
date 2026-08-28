cmake_minimum_required(VERSION 3.20)
project(SpatialEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SPATIAL_BUILD_TESTS "Build tests" ON)
option(SPATIAL_BUILD_PYTHON "Build Python bindings" ON)
option(SPATIAL_BUILD_APPS "Build apps" ON)

include(FetchContent)

if(SPATIAL_BUILD_TESTS)
  enable_testing()
endif()

add_subdirectory(engine/core)
add_subdirectory(engine/math)
add_subdirectory(engine/geometry)
add_subdirectory(engine/scene)
add_subdirectory(engine/rendering)
add_subdirectory(engine/cad)
add_subdirectory(engine/simulation)
add_subdirectory(engine/robotics)
add_subdirectory(engine/interaction)
add_subdirectory(engine/vision)
add_subdirectory(engine/hardware)
add_subdirectory(engine/io)
add_subdirectory(engine/scripting)

add_subdirectory(ui/application)
add_subdirectory(ui/viewport)

add_subdirectory(plugins/sdk)

if(SPATIAL_BUILD_APPS)
  add_subdirectory(apps/desktop)
  add_subdirectory(apps/cli)
  add_subdirectory(apps/sandbox)
endif()

if(SPATIAL_BUILD_PYTHON)
  add_subdirectory(python/api)
endif()

if(SPATIAL_BUILD_TESTS)
  add_subdirectory(tests)
endif()
