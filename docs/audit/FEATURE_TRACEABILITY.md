# Feature Traceability — Spatial Engineering Design & Simulation Platform

Audit date: 2026-11-05. Commit audited: `845dec1` (main, 18 commits).
The status of every row comes from reading the source and running it, not from the README, CHANGELOG or ROADMAP.

Legend: **Real** = working logic. **Partial** = some logic, but it does not do what the name claims. **Stub** = returns a constant or does nothing. **Mock** = UI shows hardcoded data. **Absent** = no code.

## C++ engine (`engine/`, ~1,000 lines of non-header code in total)

| Claimed feature | Where | Status | Evidence |
|---|---|---|---|
| Vec/Mat/Quat/Transform math | engine/math | Real (small) | mat.cpp 42 lines, quat.cpp 34 lines; `vec.cpp` is 2 lines (header-only types) |
| Mesh primitives (box/cylinder/sphere) | engine/geometry/src/primitives.cpp | Real | 79 lines, generates vertices and indices |
| BBox, Surface | geometry/src/bbox.cpp, surface.cpp | Stub | 2-line files |
| Curves | geometry/src/curve.cpp | Partial | 28 lines |
| Logger, EventBus, CommandStack, Uuid | engine/core | Real (minimal) | 9–35 lines each |
| Scene graph | scene/src/node.cpp | Partial | node.cpp 39 lines; scene.cpp, mesh.cpp, camera.cpp are 2-line stubs |
| Sketch entities (line/circle/arc/rect) | cad/src/sketch.cpp | Real (data only) | Stores entities; no geometry is derived from them |
| Sketch constraint solver | cad/src/sketch_solver.cpp | Stub | `bool SketchSolver::solve(Sketch&){ return true; }` |
| Extrude | cad/src/feature.cpp | **Wrong** | `return make_box({10,10,distance})` ignores the sketch. `spatial_cli --create-box` asks for 10×20×30 and writes a 10×10×30 STL (verified from the vertices) |
| Revolve | cad/src/feature.cpp | Stub | Always returns a cylinder of radius 5 and height 10 |
| Boolean | cad/src/feature.cpp | Stub | Returns operand `a` unchanged |
| Sphere part | cad/src/primitives.cpp | Stub | Returns an empty Part |
| Assembly | cad/src/assembly.cpp | Stub | Empty namespace |
| Rendering (OpenGL/Vulkan) | rendering/src | Stub | Only `NullRenderer` exists; `backend_opengl.cpp` is 2 lines; `create_renderer()` ignores the backend argument |
| FEA solver | simulation/include/simulation/fea.h | Stub | `solve()` returns the hardcoded `{true,"FEA stub",{},12.5,0.002}` |
| Thermal solver | simulation/thermal.h | Stub | Returns `"Thermal stub"` |
| Rigid-body physics | simulation/src/physics.cpp | Real (minimal) | Explicit Euler step with gravity, 19 lines |
| Forward kinematics (DH) | robotics/src/kinematics.cpp | Real | DH matrix chain |
| Inverse kinematics | robotics/src/kinematics.cpp | Stub | Fills the output with zeros and returns true |
| Jacobian | robotics | Stub | Returns the identity matrix |
| Dynamics | robotics/src/dynamics.cpp | Stub | `gravity_torque` returns `{}` |
| Trajectory | robotics/src/trajectory.cpp | Partial | 21 lines |
| Hand tracking / vision | vision/src/tracking.cpp | Stub | Returns a fixed 2-joint pose with confidence 0.9; `CameraSystem::open` opens nothing |
| Gesture recognition | interaction/src/gesture.cpp | Stub | Always returns `Point` with confidence 0.8 |
| Hardware devices | hardware/src/device.cpp | Partial | In-memory registry; `request_permission` always returns true |
| STL export | io/src/export_stl.cpp | Real | ASCII STL, atomic write |
| OBJ export | io/src/export_stl.cpp | Real | |
| STL import | io/src/export_stl.cpp | Stub | Always returns an empty mesh |
| STEP import | io/src/import_step.cpp | Absent | Empty namespace |
| Project save/load | io/src/project.cpp | Partial | Save writes only `{name, parts count, version}` with no geometry, and the name is not escaped (see TECHNICAL_DEBT P0-3). Load reads 1 KB and parses nothing |
| Asset loader | io/src/assets.cpp | Real (validation only) | 99 lines; its test `tests/integration/test_assets.cpp` is never compiled (not in CMake) |
| Python scripting | scripting/src/engine.cpp | Stub | `exec_string`/`exec_file` only log; no interpreter is embedded |
| Python bindings | python/api/src/module.cpp | Stub | `int dummy_python_api(){return 0;}`; pybind11 is OFF by default |
| Plugin SDK | plugins/sdk/src/plugin.cpp | Dead | `verified` is never set to true, so `load_plugin` always returns false |
| Desktop app (C++) | apps/desktop/src/main.cpp | Stub | Prints "headless mode (GUI requires Qt6)"; does not load the React frontend |
| CLI | apps/cli | Real (tiny) | `--create-box` produces the wrong dimensions (see Extrude) |

## Frontend (`apps/desktop/frontend`, 330 lines of source)

| Claimed feature | Status | Evidence |
|---|---|---|
| 6 workspaces (CAD/Sketch/Assembly/Simulation/Robotics/Spatial) | Mock | Tab state only; panels are identical static markup |
| Model Tree + Feature History | Mock | Hardcoded `Robot_Arm.part`, `Assembly1`, "Extrude 25mm", "Fillet 2mm" |
| 3D Viewport | Mock | 2D canvas draws a grid and an animated rectangle. "GPU: NullRenderer \| 120 FPS \| 48 tris" is a literal string |
| Shaded/Wireframe/XRay | Mock | Only changes the label text |
| Properties (Transform/Material/Simulation) | Mock | Literal "X: 0.00", "Steel — E: 210 GPa", "12.5 MPa" |
| Undo/Redo/Save/Run | Absent | Buttons have no handlers |
| File/Edit/View… menus | Absent | Buttons have no handlers |
| Engine wiring (IPC/WASM/HTTP/webview) | **Absent** | No `fetch`, WebSocket, IPC, WASM or webview code. `VITE_API_URL` in `.env.example` is unused |

## Python examples (`python/examples`)

| Example | Status | Evidence |
|---|---|---|
| box_extrude.py, robot_arm.py, simulation.py | Broken | `python -I python/examples/box_extrude.py` fails with `ModuleNotFoundError: No module named 'spatial_py'` |
| README `import spatial` snippet | Broken | No such module exists |

## Tests vs. claims

| Claim (README/commits) | Measured |
|---|---|
| "6/6 ctest" | 6/6 pass with g++ 14.2 Debug. They are smoke tests using `assert`, so they are compiled out in Release (NDEBUG) and the Release CI jobs test nothing |
| "vitest 39" passing | 44 tests: **31 pass, 13 fail** (`app.test.tsx` 7, `viewport.test.tsx` 6): `ctx.setTransform is not a function` because the jsdom canvas mock lacks it |
| `npm test` (vitest --coverage) | **Fails**: `@vitest/coverage-v8` is not installed |
| "playwright 13+11" passing | Not executed: the browser binary is missing (chromium_headless_shell-1193); no download was allowed in this audit |
| "60% coverage gate" | Cannot run (missing coverage provider) |
