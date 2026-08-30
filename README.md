# Spatial Engineering Design & Simulation Platform

Cross-platform C++ engineering platform — CAD, simulation, 3D visualization, robotics, spatial interaction.

> **Software is the platform. Future hardware is the interface.**

## Quick Start (fresh clone)

```bash
# One-command bootstrap (C++ + frontend + tests)
./scripts/bootstrap.sh          # Linux/macOS
# or
scripts\bootstrap.bat           # Windows

# Or manually (cross-platform)
cmake -S . -B build -G Ninja   # or -G "MinGW Makefiles" on Windows
cmake --build build
ctest --test-dir build --output-on-failure

cd apps/desktop/frontend
npm ci --legacy-peer-deps
npm run build
npm test                        # vitest 39 + playwright 13+11
```

## Docker / Devcontainer (reproducible)

```bash
docker build -t spatial .
docker run -it -p 5173:5173 spatial

# VS Code: Reopen in Container (uses .devcontainer/devcontainer.json)
```

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

## Coverage
`vitest --coverage` (threshold 60%) + `ctest` + `gcov/lcov` for C++ — gated in CI

## Env
Copy `.env.example` → `.env` (never commit secrets)
