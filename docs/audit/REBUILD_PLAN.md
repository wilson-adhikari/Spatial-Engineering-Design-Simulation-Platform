# Rebuild Plan — Spatial Engineering Design & Simulation Platform

Audit date: 2026-11-05. This plan is a proposal, not something already done. The founder approves scope, licence and stack.

## Position
The repo is a **scaffold with hardening code around stubs**. About 1,000 lines of C++ implementation sit behind headers whose names promise CAD/FEA/robotics/vision. The React UI is a static mock that has no channel to the engine. The parts worth keeping are the directory layout, the math/geometry primitives, STL/OBJ export, forward kinematics and the UI shell. Do **not** rewrite blindly. Fix the build and the honesty problems first, then build one vertical slice end-to-end.

## Milestone 0 — Make it honest and green (1–2 days)
Objective: CI reflects reality.
1. Add a `LICENSE` (founder decision: proprietary vs OSS). The repo is public with no licence.
2. Frontend: add `src/vite-env.d.ts` (`/// <reference types="vite/client" />`), so the `tsc` build passes. Add a `setTransform` stub to the `tests/setup.ts` canvas mock (13 failing tests). Add `@vitest/coverage-v8` pinned to the vitest major. Migrate `.eslintrc.cjs` to `eslint.config.js`, or pin eslint 8, and upgrade `eslint-plugin-jsx-a11y` so `npm ci` works without `--legacy-peer-deps`.
3. C++ tests: replace `assert` with a check that survives NDEBUG (or add GoogleTest/Catch2), and register `test_assets.cpp`.
4. CI: remove `|| true` from clang-tidy/format/prettier, or delete those steps. Install the Playwright browser version that matches the lockfile.
5. README/CHANGELOG/SECURITY/ROADMAP: mark stubs as stubs. Remove the "Stage 2/3 ✅" claims and the "Python API" example until they are real.
Verification: `npm ci && npm run build && npm test`, `ctest -C Release`, all green in CI.

## Milestone 1 — Correctness of what exists (2–4 days)
- Extrude must use the sketch profile (rectangle/circle → prism). Add a regression test asserting that a 10×20×30 box has a bbox of 10×20×30.
- Project save: serialize through a real JSON writer (escape names) and include parts. Load: parse and round-trip test.
- Remove or clearly gate dead/fake APIs: `SketchSolver::solve`, `KinematicChain::inverse`, `FEASolver::solve`, `HandTracker::track`, `GestureRecognizer`, `PluginManager::load_plugin`. Return "not implemented" errors instead of fake success values.

## Milestone 2 — Engine ↔ UI vertical slice (1–2 weeks)
Decision needed: how the UI talks to the engine. Options, smallest first:
1. **WASM** (Emscripten build of math/geometry/cad/io) called from React. One process, works in the browser, no IPC.
2. **Local HTTP/WebSocket** sidecar (C++ or a Python/FastAPI wrapper via pybind11).
3. **Native shell** (Qt WebEngine or Tauri) hosting the React UI with an IPC bridge.
Slice: "sketch rectangle → extrude → see real mesh in viewport (three.js or WebGL) → export STL", with Playwright E2E covering it.

## Milestone 3 — Pick the product's real differentiator
CAD kernel work (booleans, fillets, STEP) should reuse OpenCascade (LGPL, a licence review is needed) rather than be hand-written. FEA should reuse an established solver (e.g. CalculiX/FEniCS/Gmsh pipeline). Robotics should use ROS 2/KDL per company standards. Decide which one module ships first, and gate premium simulation behind server-side entitlements per company policy (§8).

## Out of scope until M2 is done
Vision/hand tracking, hardware devices, plugin SDK, scripting sandbox. Delete or move these to `experimental/` so they stop inflating the audit surface.

## Dependabot handling
See REPOSITORY_AUDIT.md § "Dependabot PR verdicts". Merge the GitHub Actions bumps after fixing the CI breakages in M0. Merge the npm bumps individually after M0 makes the build green, so failures are attributable. Close the react-dom 19 PR (it does not bump `react`).
