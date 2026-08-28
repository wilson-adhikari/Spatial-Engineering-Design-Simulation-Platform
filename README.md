# Spatial Engineering Design & Simulation Platform

Cross-platform C++ engineering platform — CAD, simulation, 3D visualization, robotics, spatial interaction.

> **Software is the platform. Future hardware is the interface.**

## Architecture
```
Application UI / Spatial UI -> Command System -> Engineering Core (CAD/Math/Scene/Simulation) -> Rendering Engine -> Hardware Abstraction
```

## Structure
See `docs/ARCHITECTURE.md`. Full spec in concept doc v1.0.

## Build
```bash
cmake --preset dev
cmake --build build/dev
ctest --test-dir build/dev
```

Requirements: CMake 3.20+, C++20, Ninja or MSVC 2022.

## Python
```python
import spatial
project = spatial.create_project()
part = project.create_part()
sketch = part.create_sketch("XY")
sketch.circle(center=(0,0), radius=25)
part.extrude(sketch, distance=50)
project.save("robot_arm.part")
```
See `python/examples/`.

## MVP Status
- [x] Core, Math, Geometry, Commands, Scene
- [x] Rendering abstraction, Viewport
- [x] Parametric CAD primitives + extrude/boolean
- [x] Project save/load, undo/redo, autosave
- [x] Plugin SDK, Hardware abstraction, Python bindings stub

## License
Proprietary — All rights reserved.
