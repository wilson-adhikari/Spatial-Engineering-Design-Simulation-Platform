# Spatial Engineering Design & Simulation Platform

Cross-platform C++ engineering platform — CAD, simulation, 3D visualization, robotics, spatial interaction.

> **Software is the platform. Future hardware is the interface.**

## Architecture
```
Application UI / Spatial UI -> Command System -> Engineering Core (CAD/Math/Scene/Simulation) -> Rendering Engine -> Hardware Abstraction
```

## Desktop UI — ReUI

Professional engineering layout built with **React + Tailwind + ReUI** (shadcn registry):

```
File Edit View Design Simulation Tools Help
[CAD|Sketch|Assembly|Simulation|Robotics|Spatial]   [Shaded|Wireframe|XRay]
Model Tree | 3D Viewport (canvas) | Properties
Status / Selection / Coordinates
```

Location: `apps/desktop/frontend/` — see its README for `npm install` / `npx shadcn add @reui/*`

Features: Model Tree + Feature History, Viewport with tools/selection/grid, Properties (Transform/Material/Simulation/Python), Workspaces per §8.

## Build (C++ Core)

```bash
cmake --preset dev
cmake --build build/dev
ctest --test-dir build/dev
# Windows MinGW:
& "C:\cmake-3.29.3-windows-x86_64\bin\cmake.exe" -S . -B build/test -G "MinGW Makefiles"
& "C:\cmake-3.29.3-windows-x86_64\bin\cmake.exe" --build build/test
```

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

## Structure
See `docs/ARCHITECTURE.md` — engine/core, math, geometry, cad, scene, rendering, simulation, robotics, interaction, vision, hardware, io, scripting

