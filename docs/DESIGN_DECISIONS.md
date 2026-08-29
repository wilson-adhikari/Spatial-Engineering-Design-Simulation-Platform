# Design Decisions (ADR)

## ADR-001: C++20 as Primary Language
**Decision:** C++ for CAD/geometry/rendering/simulation. Python as scripting.
**Rationale:** Performance, deterministic memory, GPU interop, existing CAD kernels.
**Consequence:** Requires hardening (-fstack-protector, finite checks).

## ADR-002: Modular Static Libs
**Decision:** Each engine/* is a static lib with PUBLIC include.
**Rationale:** Independently testable, clear interface, reproducible.

## ADR-003: Command System for Undo/Redo
**Decision:** All mutations via Command with execute/undo, CommandStack mutex MAX 1000.
**Rationale:** Enables macro/scripting/gesture, transactional.

## ADR-004: ReUI over Qt for Desktop Frontend
**Decision:** React+Tailwind+ReUI (shadcn) for UI, C++ for engine, bridge via Tauri/WASM later.
**Rationale:** 966+ patterns, faster iteration, CSP, a11y, visual regression.

## ADR-005: Atomic File IO
**Decision:** Save via .tmp + rename, is_safe_path (no .., absolute, 1024, null), caps 100/200MB.
**Rationale:** Prevent traversal, race, bomb.

## ADR-006: Disabled-by-Default Scripting
**Decision:** ScriptEngine enabled_=false, perm bitmask, blocklist eval/os/subprocess, 1MB cap.
**Rationale:** Mitigate RCE.

## ADR-007: AssetLoader Allowlist
**Decision:** Only assets/ prefix, ext allowlist, 64KB JSON/50MB model/32MB texture, magic PNG/JPG.
**Rationale:** Supply-chain, bomb.

## ADR-008: Test Pyramid
**Decision:** Unit (Vitest 39), Integration (ctest 5), E2E (Playwright 13), Visual, A11y, Responsive.
**Rationale:** Aggressive coverage, early regression.

## ADR-009: Reproducible Builds
**Decision:** Pin deps (package-lock, CMake FetchContent hash), SBOM, hidden visibility.
**Rationale:** Determinism, audit.

## ADR-010: Incremental Roadmap Stage 1-8
**Decision:** Foundation→3D→CAD MVP→Pro CAD→Sim→Robotics→Spatial→Display.
**Rationale:** MVP early, long-term vision.
