# Architecture — Spatial Engineering Platform v0.1

> Software is the platform. Future hardware is the interface.

## 1. Layered Overview (§5)
```
Application UI / Spatial UI  (ReUI + Viewport)
        ↓
    Command System (undo/redo, macro, scripting)
        ↓
Engineering Core ─┬─ CAD (Part/Sketch/Feature/Assembly)
                  ├─ Math (Vec/Mat/Quat/Transform)
                  ├─ Geometry (BBox/Ray/Plane/Curve/Surface)
                  ├─ Scene (Node/Mesh/Camera)
                  └─ Simulation/Robotics (Solver/FEA/Physics/Kinematics)
        ↓
Rendering Engine (IRenderer → OpenGL/Vulkan/Software)
        ↓
Hardware Abstraction (DeviceManager, Camera, Haptics, IMU)
        ↓
OS / GPU / Camera / Device Layer
```

Modularity: each subsystem has clear interface, independently testable, static lib.

## 2. Directory Map (§41)
```
apps/desktop/frontend (ReUI) | apps/desktop (C++ app) | apps/cli | apps/sandbox
engine/core,math,geometry,scene,rendering,cad,simulation,robotics,interaction,vision,hardware,io,scripting
ui/application,viewport,panels,dialogs,themes
python/api,examples
tests/unit,integration,regression,performance
assets/models,materials,textures
docs, third_party, tools
```

## 3. Core Subsystems
**Core**: Logger (level), Result<T> (ok/err), Uuid (mutex+CSPRNG), EventBus (Id/topic), CommandStack (mutex, MAX 1000), LinearArena (cap 1<<20, mutex)
**Math**: Vec2/3/4 finite+normalized guards, Mat4 identity/translate/scale/rotate/perspective/orthographic/look_at with finite+range validation, Quat slerp with clamp, Transform matrix
**Geometry**: MeshData vertices/indices/normals/bbox, primitives with DoS caps (box/cylinder/sphere/torus), BBox numeric_limits, Ray/Plane
**Scene**: Node (parent weak_ptr, MAX_CHILDREN 10k, cycle depth 128), Mesh, Camera (fov 0-π), Scene (root, camera, meshes map)
**Rendering**: IRenderer (init/begin/draw/end/stats), NullRenderer, Material (PBR)
**CAD**: Sketch (MAX 10k entities, plane XY/XZ/YZ), Constraint, SketchSolver, Feature (Extrude/Revolve/Boolean), Part (MAX 1k), Assembly JointType Fixed/Revolute/...
**Simulation**: ISolver, SolverRegistry (mutex), PhysicsWorld (MAX 10k bodies, dt (0,1]), FEA/Thermal stubs
**Robotics**: DHParam, Joint, KinematicChain MAX_JOINTS 32, forward/inverse/jacobian, Trajectory MAX_WP 10k
**Interaction**: GestureRecognizer, InputSystem via EventBus
**Vision**: HandTracker MAX_JOINTS 64, CameraSystem
**Hardware**: DeviceManager mutex, permission gate, verified-only plugin load
**IO**: Project atomic .tmp+rename, is_safe_path (no .., absolute, null, 1024), 100MB cap, export_stl 200MB, AssetLoader (64KB JSON, 50MB model, 32MB texture, magic)
**Scripting**: ScriptEngine disabled-by-default, perm bitmask, blocklist, 1MB cap

## 4. UI (§8-9)
ReUI (shadcn+Tailwind+Motion): ModelTree/FeatureHistory, Viewport canvas (grid/axes, perspective/ortho, selection), Properties (Transform/Material/Simulation/Python), Status bar. Workspaces: CAD/Sketch/Assembly/Simulation/Robotics/Spatial. Viewport independent rendering surface for future spatial displays.

## 5. Command System (§28)
Every operation is a Command (name/execute/undo/can_undo). Stack provides undo/redo/automation/macro/scripting/gesture integration.

## 6. Rendering & Spatial Display (§24,29)
CAD → Scene → Rendering API (Vulkan/OpenGL) → GPU. SpatialRenderer → Spatial Display API → hardware (monitor/VR/AR/light-field). CAD engine has no holographic assumptions.

## 7. Data Flow Example
Sketch → Feature → Part.build() → MeshData → Scene.add_mesh → IRenderer.draw_scene → Viewport

## 8. Security Boundaries
IO validates paths, sizes, finite; Hardware permission; Scripting disabled; Plugin verified-only; Frontend CSP + sanitized ids + pinned deps.

## 9. Build & Test
CMake 3.20+, C++20, Ninja/MSVC/MinGW. `cmake --preset dev && cmake --build && ctest`. Frontend `npm --legacy-peer-deps && npx playwright install chromium`.

## 10. Future (Stage 4-8)
Advanced CAD (booleans, sweeps), FEM full, Robotics motion planning, Spatial Interaction (hand tracking), Spatial Display (multi-view).
