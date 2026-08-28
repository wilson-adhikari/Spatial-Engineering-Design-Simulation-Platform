add_library(spatial_ui STATIC src/app.cpp src/panel.cpp)
target_include_directories(spatial_ui PUBLIC include)
target_link_libraries(spatial_ui PUBLIC spatial_core spatial_scene spatial_io spatial_scripting)

