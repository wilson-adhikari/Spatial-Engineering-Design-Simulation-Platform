add_executable(example_box cad_box.cpp)
target_link_libraries(example_box PRIVATE spatial_cad spatial_io)
add_executable(example_assembly assembly.cpp)
target_link_libraries(example_assembly PRIVATE spatial_cad)

