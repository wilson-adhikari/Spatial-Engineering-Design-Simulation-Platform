add_executable(spatial_desktop src/main.cpp)
target_link_libraries(spatial_desktop PRIVATE spatial_ui spatial_viewport spatial_cad spatial_io spatial_scripting)

# ReUI frontend (optional, needs Node)
# cd frontend && npm install && npm run build
# frontend/dist will be embedded via RC or served via webview

