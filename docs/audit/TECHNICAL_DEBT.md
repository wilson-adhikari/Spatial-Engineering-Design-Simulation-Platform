# Technical Debt — Spatial Engineering Design & Simulation Platform

Audit date: 2026-11-05, commit `845dec1`. Every item was verified in code or by execution unless it is marked *(read only)*.

## P0 — Blocks release / misrepresents the product

| ID | Item | Evidence | Fix |
|---|---|---|---|
| P0-1 | **No LICENSE file** in a public repo | `ls LICENSE*` → none; README/docs carry no licence | Founder picks a licence; add `LICENSE` |
| P0-2 | **Frontend build fails** (`npm run build`) | `tsc --noEmit` → `src/lib/logger.ts(6,41): TS2339 Property 'env' does not exist on type 'ImportMeta'`. There is no `vite-env.d.ts`. `vite build` alone succeeds | Add `src/vite-env.d.ts` |
| P0-3 | **Project file JSON injection / corruption** | `project.cpp` streams `name` unescaped into JSON. A probe built against the real libs: `set_name("a\",\"pwn\":true,\"x\":\"")` returns true, and save writes `{"name":"a","pwn":true,"x":"", "parts":0, "version":1}` | Use a JSON library or escape the string; validate the charset in `set_name` |
| P0-4 | **UI is a mock, not wired to the engine** | No fetch/IPC/WASM/webview anywhere in `src/`. The viewport draws a rectangle; "NullRenderer \| 120 FPS \| 48 tris" and "12.5 MPa" are literals. The C++ `spatial_desktop` prints "headless mode (GUI requires Qt6)" | See REBUILD_PLAN M2 |
| P0-5 | **Docs and commits claim features and test results that do not hold** | README "Python API", ROADMAP "Stage 2/3 ✅", commit `d04c9b9` "39 vitest, 13+11 playwright" passing. Measured: 13/44 vitest fail, `npm test` cannot run, Python examples raise `ModuleNotFoundError`, FEA/IK/solver/booleans are stubs returning fake success | Correct docs; turn fake-success stubs into explicit "not implemented" |
| P0-6 | **Extrude ignores the sketch** | `ExtrudeFeature::evaluate` returns `make_box({10,10,distance})`. `spatial_cli --create-box` requests 10×20×30 and the exported STL vertices span ±5, ±5, ±15 (10×10×30) | Implement the profile extrude, plus a bbox regression test |

## P1 — Broken engineering hygiene / CI

| ID | Item | Evidence |
|---|---|---|
| P1-1 | 13 component tests fail | `ctx.setTransform is not a function`: the jsdom canvas mock in `tests/setup.ts` lacks `setTransform`/`font` (app.test.tsx 7, viewport.test.tsx 6) |
| P1-2 | `npm test` / coverage gate cannot run | `MISSING DEPENDENCY @vitest/coverage-v8` |
| P1-3 | `npm ci` fails without `--legacy-peer-deps` | `eslint-plugin-jsx-a11y@6.8.0` peers `eslint ^3–8`; the project pins `eslint 9.9.0` |
| P1-4 | `npm run lint` fails | eslint 9 ignores `.eslintrc.cjs` and needs `eslint.config.js`. The CI `static-analysis` eslint step has no `|| true`, so the job fails |
| P1-5 | C++ tests are no-ops in Release | All tests use `assert`; the CI matrix runs Release, where NDEBUG removes them |
| P1-6 | `tests/integration/test_assets.cpp` is never built | Not listed in `tests/integration/CMakeLists.txt` |
| P1-7 | CI security/format gates are cosmetic | clang-tidy, clang-format and prettier steps end in `|| true`. clang-tidy uses the glob `engine/**/*.cpp` without globstar |
| P1-8 | Playwright E2E could not be run locally | `@playwright/test@1.55.1` needs `chromium_headless_shell-1193` (not installed). With 1.62.1 see the Dependabot section in REPOSITORY_AUDIT.md |
| P1-9 | npm audit: 9 vulnerabilities (4 moderate, 3 high, 2 critical), all in dev dependencies | `npm audit` (prod-only: 0). Includes tinypool (critical, via vitest 1.x) and esbuild ≤0.24.2 (via vite 5) |

## P2 — Design / correctness debt

| ID | Item | Evidence |
|---|---|---|
| P2-1 | Fake-success stubs | `SketchSolver::solve` returns true; `KinematicChain::inverse` returns zeros + true; `jacobian` returns identity; `FEASolver::solve` returns hardcoded 12.5; `HandTracker::track` returns a fixed pose; `GestureRecognizer` always returns Point |
| P2-2 | Project load parses nothing; save omits geometry | `Project::load` reads 1 KB into a buffer and returns true |
| P2-3 | Plugin loading is dead code | `verified` is never set to true, so `load_plugin` always fails |
| P2-4 | `DeviceManager::request_permission` always grants | device.cpp |
| P2-5 | Scripting "sandbox" is a string blocklist that executes nothing | `is_safe_code` greps for `import os`/`eval(`; trivially bypassable if an interpreter is ever attached. SECURITY.md claims "timeouts", but none exist |
| P2-6 | `create_renderer(Backend)` ignores its argument | Always `NullRenderer` |
| P2-7 | STL import and STEP import are empty | `import_stl` returns `{}`; `import_step.cpp` is an empty namespace |
| P2-8 | Path validation is duplicated in 4 places with different rules | project.cpp, export_stl.cpp, scripting/engine.cpp, plugin.cpp |
| P2-9 | Uuid reseeds an mt19937_64 from `random_device` on every call and is documented as "CSPRNG" | uuid.cpp; mt19937 is not a CSPRNG |
| P2-10 | Model Tree items are clickable `<div>`s with no keyboard or role support | ModelTree.tsx (a11y) |

## P3 — Housekeeping

| ID | Item |
|---|---|
| P3-1 | 30+ files of 1–3 lines (`namespace x{}`) inflate the module count; delete them or mark them as placeholders |
| P3-2 | `ui/` C++ tree (Qt-oriented panels/dialogs/themes) duplicates the React UI and is mostly empty |
| P3-3 | CHANGELOG has 3 releases on one day (0.1.0–0.3.0), but no git tags exist; `CMakeLists` says 0.1.0 |
| P3-4 | `SECURITY.md` contact `security@spatial.local` is not a routable address |
| P3-5 | Dependabot npm `open-pull-requests-limit: 5` hides further updates; no grouping configured |
| P3-6 | Engine code style: whole functions on single lines, which makes review and diffs hard; `.clang-format` exists but is not enforced |
| P3-7 | `.env.example` `VITE_API_URL` is unused (there is no API) |
