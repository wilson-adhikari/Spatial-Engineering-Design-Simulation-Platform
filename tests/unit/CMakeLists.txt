add_executable(test_math test_math.cpp)
target_link_libraries(test_math PRIVATE spatial_math spatial_geometry spatial_cad spatial_core)
add_test(NAME math COMMAND test_math)

add_executable(test_geometry test_geometry.cpp)
target_link_libraries(test_geometry PRIVATE spatial_math spatial_geometry spatial_cad spatial_core)
add_test(NAME geometry COMMAND test_geometry)

add_executable(test_cad test_cad.cpp)
target_link_libraries(test_cad PRIVATE spatial_math spatial_geometry spatial_cad spatial_core)
add_test(NAME cad COMMAND test_cad)

add_executable(test_commands test_commands.cpp)
target_link_libraries(test_commands PRIVATE spatial_math spatial_geometry spatial_cad spatial_core)
add_test(NAME commands COMMAND test_commands)

