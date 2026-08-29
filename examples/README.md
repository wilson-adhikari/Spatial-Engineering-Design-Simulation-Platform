# Examples

## Python (first-class)
- `python/examples/robot_arm.py` — circle + extrude 50
- `python/examples/box_extrude.py` — rectangle extrude 20
- `python/examples/simulation.py` — FEA stub

Run: `python python/examples/robot_arm.py` (needs `spatial_py` built with `-DSPATIAL_PYTHON_BINDINGS=ON`)

## C++ (engine)
- `examples/cad_box.cpp` — make_box + export_stl
- `examples/assembly.cpp` — 2-part assembly
- `examples/kinematics.cpp` — 2-DOF chain forward

Build: `cmake -S . -B build && cmake --build build --target examples`

## Frontend ReUI
- `apps/desktop/frontend/src/App.tsx` — workspaces, viewport modes
- `npm run dev` — see ModelTree/Viewport/Properties

## Assets
- `assets/models/primitive_box.stl` imported via `AssetLoader::load_model`
- `assets/materials/steel.json` via `load_material`
