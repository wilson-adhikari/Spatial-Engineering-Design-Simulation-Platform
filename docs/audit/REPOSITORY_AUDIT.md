# Repository Audit — Spatial Engineering Design & Simulation Platform

- Audit date: 2026-11-05
- Commit: `845dec1` on `main` (18 commits, all 2026-08)
- Auditor: Claude Code (AI). Founder review required.
- Companion files: FEATURE_TRACEABILITY.md, TECHNICAL_DEBT.md (P0–P3), REBUILD_PLAN.md

## 1. Verdict
A **scaffold with stubbed modules and a static UI mock**.
- The C++ engine compiles cleanly and its 6 smoke tests pass.
- Most named capabilities (FEA, IK, sketch solver, booleans, rendering, vision, Python API, STEP/STL import) are stubs. Several of them return fake success values.
- The React UI is not connected to the engine in any way.
- The frontend `npm run build` fails on `main`, and 13 of 44 component tests fail. This contradicts the commit messages and README.
- There is no licence file.

## 2. What was executed (and what was not)
All execution happened in scratch copies under the session scratchpad. The repo was modified only by adding these four files.

| Step | Command | Result |
|---|---|---|
| Frontend install (strict) | `npm ci` | **FAIL**: ERESOLVE, eslint-plugin-jsx-a11y@6.8.0 needs eslint ≤8, project pins 9.9.0 |
| Frontend install (as CI does) | `npm ci --legacy-peer-deps` | OK |
| Frontend build | `npm run build` (= `tsc --noEmit && vite build`) | **FAIL**: `src/lib/logger.ts(6,41) TS2339 'env' does not exist on type 'ImportMeta'` |
| Bundle only | `npx vite build` | OK (189 kB JS) |
| Unit tests (scripted) | `npm test` (= `vitest run --coverage`) | **FAIL**: missing `@vitest/coverage-v8` |
| Unit tests | `npx vitest run --config vitest.config.ts` | **31 pass / 13 fail** (44). Cause: canvas mock lacks `setTransform` |
| Lint | `npx eslint . --max-warnings 0` | **FAIL**: eslint 9 requires `eslint.config.js`; repo has `.eslintrc.cjs` |
| E2E | `npx playwright test --config=playwright.config.ts` | **NOT EXECUTED**: browser binary `chromium_headless_shell-1193` is not installed (download not permitted in this audit). All 13 error at launch |
| a11y / visual / responsive Playwright | — | Not executed (same reason) |
| npm audit | `npm audit` | 9 vulns (2 critical, 3 high, 4 moderate), all dev dependencies; `--omit=dev` → 0 |
| Toolchain | `cmake` not on PATH; installed `cmake 4.4.4` + `ninja` via pip into a scratch venv. Compiler: MSYS2 `g++ 14.2.0`. MSVC `cl` not on PATH | — |
| C++ configure + build | `cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug` + `cmake --build` | **OK**: 83/83 targets, **0 warnings** with `-Wall -Wextra -Wpedantic` |
| C++ tests | `ctest` | **6/6 pass** (math, geometry, cad, commands, integration, bench). Debug only; Release (NDEBUG) not run |
| CLI | `spatial_cli --create-box` | Runs, but the box has wrong dimensions (see §5) |
| Desktop exe | `spatial_desktop` | Prints "headless mode (GUI requires Qt6)", exit 0. There is no GUI |
| Python examples | `python -I python/examples/box_extrude.py` | **FAIL**: `ModuleNotFoundError: No module named 'spatial_py'` |
| Diagnostic probe (scratch) | Adding `src/vite-env.d.ts` + `setTransform` to the mock | Build passes; vitest 42/44 (2 remaining assertion failures: viewport canvas width 0≠1200 in jsdom; no button named /shaded/i) |
| Not done | MSVC build, Release build, macOS/Linux, sanitizers, coverage, Docker/devcontainer, GitHub Actions runs | — |

## 3. Inventory
- **Size**: ~2,200 lines total across C++/CMake/Python/scripts (excluding the frontend); ~1,000 lines of C++ implementation. Frontend: 330 lines of source plus 7 component test files and 4 Playwright suites.
- **Languages**: C++20 (engine/ui/apps), TypeScript/React 18 (frontend), Python (3 examples, no real binding).
- **CMake**: 26 `CMakeLists.txt` files; 13 engine static libraries, ui/application, ui/viewport, plugins/sdk, apps (desktop, cli, sandbox), python/api (pybind11 OFF → interface stub), tests.
- **package.json**: one (`apps/desktop/frontend`), with a lockfile present.
- **Tests**: 4 C++ unit tests, 1 integration test, 1 bench (registered). `test_assets.cpp` exists but is not built. `tests/regression` holds only a README. Frontend: 44 vitest tests, 13 E2E, plus a11y/visual/responsive specs.
- **CI**: `.github/workflows/ci.yml`, with jobs cpp (3 OS × Debug/Release), cpp-coverage, frontend, static-analysis, dependency-scan (super-linter, sbom), and release on tags.
- **Dependabot**: npm (frontend) + github-actions, weekly.
- **Licence**: **none** (no LICENSE/COPYING; no licence field). Assets READMEs claim "CC0 original", which was not verified.
- **Git**: 18 commits, single author-style history; no tags despite CHANGELOG 0.1.0–0.3.0.

## 4. Module reality (C++)
Real but small: math, geometry primitives, core (logger/event/command/uuid), forward kinematics, Euler physics step, STL/OBJ export, asset path validation.
Stub or fake: rendering (NullRenderer only), FEA/thermal, sketch solver, revolve/boolean/sphere, assembly, IK/Jacobian/dynamics, vision, gestures, scripting (logs only), Python bindings, STEP/STL import, project load, plugin loading.
Full per-feature table: FEATURE_TRACEABILITY.md.

## 5. UI ↔ engine wiring: **mock**
- `src/` contains no `fetch`, WebSocket, IPC, WASM, Electron/Tauri or webview code.
- The Viewport is a 2D canvas animating a rectangle; the "GPU: NullRenderer | 120 FPS | 48 tris" text is hardcoded.
- Model Tree, Feature History and Properties ("Steel — E: 210 GPa", "12.5 MPa") are literals. "12.5" matches the hardcoded return of `FEASolver::solve()`, which makes it look integrated when it is not.
- Undo/Redo/Save/Run and the menus have no handlers.
- `apps/desktop/CMakeLists.txt` only comments that `frontend/dist` "will be embedded".
- `.env.example` `VITE_API_URL` is unused.

## 6. Security findings
1. **Project JSON injection (P0)**. `Project::save` writes `name` unescaped. A probe built against the compiled libs showed `set_name("a\",\"pwn\":true,\"x\":\"")` accepted, producing `{"name":"a","pwn":true,"x":"", ...}`. This is low impact today because load parses nothing, but it becomes real when a parser is added.
2. **Scripting "sandbox"** is a substring blocklist (`import os`, `eval(`). It does nothing now (there is no interpreter), but it must not be relied on. SECURITY.md claims timeouts that do not exist.
3. `DeviceManager::request_permission` always returns true; the permission gate is nominal.
4. Uuid is described as a "CSPRNG" but is an `mt19937_64` reseeded per call. It is fine for IDs, not for secrets.
5. Path checks are reasonable (they reject `..`, absolute paths and NUL) but are duplicated 4× with different rules.
6. The frontend has a CSP meta in `index.html` and a dev server bound to 127.0.0.1. Good.
7. npm audit: 2 critical + 3 high in dev tooling (tinypool via vitest 1.x, esbuild via vite 5, brace-expansion, source-map-js). None in production dependencies.
8. Secrets: no credentials found in tracked files. `.env.example` holds placeholders only (values not printed here).
9. CI security gates (clang-tidy, clang-format, prettier) end in `|| true`, so they never fail.

## 7. Documentation accuracy
| Claim | Reality |
|---|---|
| README `npm test  # vitest 39 + playwright 13+11` | `npm test` errors (no coverage provider); vitest is 31/44 |
| Commit d04c9b9 "39 vitest, 13+11 playwright" passing | Not reproducible on this commit |
| README Python API (`import spatial`) | No such module; examples import `spatial_py`, which is a C stub |
| ROADMAP "Stage 2 3D Engine ✅, Stage 3 CAD MVP ✅ (Constraints, Extrude)" | Renderer is null; constraint solver returns true; extrude ignores the sketch |
| SECURITY.md "Deps pinned exact versions" | `vite ^5.4.21`, `@playwright/test ^1.55.1`, `vitest ^1.6.1` etc. are caret ranges |
| models/README "Import via: spatial_cli --import" | The CLI has no `--import` flag |
| README "Coverage gated in CI" | The provider package is missing, so the gate cannot run |

## 8. Dependabot PR verdicts
The local clone has **10** `origin/dependabot/*` branches; the brief reports 9 open PRs. PR numbers are not stored in git, and no GitHub API call was made (network restricted to npm/pip). Verdicts are therefore keyed by branch. **Map numbers #1–#9 against GitHub before acting.** Only #9 = react-dom/@types/react-dom is stated by the brief. One of the 10 branches is likely tied to a closed or superseded PR.

Baseline on `main` for comparison: tsc FAIL, vite build OK, vitest 31/44, strict `npm install` ERESOLVE (pre-existing eslint peer conflict). Each npm bump was tested alone from a reset lockfile with `--legacy-peer-deps`.

| PR | Branch / change | tsc | vite build | vitest | Verdict | Evidence / notes |
|---|---|---|---|---|---|---|
| #9 | `npm_and_yarn/.../multi-15e0f44842`: react-dom 18.3.1→**19.2.8**, @types/react-dom→19.2.5 | FAIL (pre-existing) | OK | **0 tests run, 7/7 files fail**: `TypeError: Cannot read properties of undefined (reading 'S')` | **Needs changes: do not merge** | react-dom 19.2.8 peers `react ^19.2.8`; the PR leaves `react 18.3.1`. Either close it and pin react-dom/@types/react-dom to 18 (react-dom 18.3.1 + @types/react-dom 18.3.7 tested: same as baseline, 31/44), or do a deliberate React 19 upgrade (react, react-dom, @types/react, testing-library) as one change. npm latest is react/react-dom 19.3.1 |
| (verify #) | `.../vite-8.2.2`: vite ^5.4.21→^8.2.2 | FAIL (pre-existing) | **OK** (183 kB) | 31/44 (= baseline) | **Merge-safe after M0 fixes** | No regression. With the tsc fix + canvas mock applied in scratch: build OK, vitest 42/44 (same as on vite 5). vitest 1.x still uses its own vite; plan a vitest upgrade (clears the tinypool/esbuild advisories). Major version jump, so the dev server/E2E were not exercised |
| (verify #) | `.../playwright/test-1.62.1`: @playwright/test ^1.55.1→^1.62.1 | FAIL (pre-existing) | OK | 31/44 | **Needs changes** (small) | `package.json` also pins `playwright ^1.55.1` separately; bump both so the CLI and test runner agree. E2E not executed: 1.62.1 needs `chromium_headless_shell-1234` (not installed). CI runs `playwright install` so it should work there; unverified |
| (verify #) | `.../radix-ui/react-dialog-1.1.23`: 1.1.1→1.1.23 | FAIL (pre-existing) | OK | 31/44 | **Merge-safe** | Patch-level; not imported anywhere (unused dependency; `react-dropdown-menu` likewise) |
| (verify #) | `.../radix-ui/react-separator-1.1.15`: 1.1.0→1.1.15 | FAIL (pre-existing) | OK | 31/44 | **Merge-safe** | Patch-level. No `@radix-ui/*` package is imported anywhere in `src/` or `tests/` (`ui/separator.tsx` is a plain div), so both radix dependencies are currently unused and could be removed instead |
| (verify #) | `github_actions/actions/checkout-7`: v4→v7 (6 uses) | n/a | n/a | n/a | **Merge-safe (CI-unverified)** | Only the `uses:` tag changes; no inputs used. Cannot run Actions locally |
| (verify #) | `github_actions/actions/setup-node-7`: v4→v7 | n/a | n/a | n/a | **Merge-safe (CI-unverified)** | Inputs used (`node-version`, `cache`, `cache-dependency-path`) are long-standing |
| (verify #) | `github_actions/actions/upload-artifact-7`: v4→v7 (3 uses) | n/a | n/a | n/a | **Merge-safe (CI-unverified)** | Artifact names are unique per job. The `coverage-lcov` upload will still find no file until the coverage provider is added |
| (verify #) | `github_actions/github/super-linter-7`: v6→v7 | n/a | n/a | n/a | **Needs changes** (config) | The job runs super-linter with no config over the whole repo and has no `fetch-depth: 0`/`GITHUB_TOKEN` env. It is likely failing on v6 already; v7 changes linter set. Configure `VALIDATE_*` first or drop it |
| (verify #) | `github_actions/softprops/action-gh-release-3`: v2→v3 | n/a | n/a | n/a | **Merge-safe (CI-unverified)** | Only runs on `v*` tags (none exist). The `files:` list references `sbom.json`, which no step creates |

Overall: no npm bump fixes or worsens the failing baseline except react-dom 19, which breaks every test. Merge order recommendation: M0 fixes (tsc, canvas mock, coverage provider, eslint) → radix ×2 → Actions ×3 + gh-release → playwright (with `playwright` also bumped) → vite 8 → close react-dom 19 (or a planned React 19 migration).

## 9. Top defects
1. Frontend build broken on `main` (missing `vite-env.d.ts`).
2. UI is a hardcoded mock with no engine connection; the desktop C++ app has no GUI.
3. Extrude ignores sketch geometry: CLI "10×20×30 box" outputs 10×10×30.
4. Project save JSON injection / no real serialization; load parses nothing.
5. No LICENSE in a public repo, and docs/commits claim passing tests and completed features that are not real.
