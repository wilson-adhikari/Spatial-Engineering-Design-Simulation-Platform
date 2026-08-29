add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE spatial_geometry)
add_test(NAME bench COMMAND bench)

