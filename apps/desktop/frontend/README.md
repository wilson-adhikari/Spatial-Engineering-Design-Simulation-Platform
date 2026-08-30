# Spatial Desktop — ReUI

React + Tailwind + ReUI (shadcn registry) frontend for the C++ Spatial Engine.

## Install (requires Node 20.18.1)

```powershell
cd apps/desktop/frontend
npm ci --legacy-peer-deps   # reproducible from package-lock.json
npm run dev      # http://127.0.0.1:5173
npm run build    # vite build
```

## Tests (self-contained, no external services)

All tests run offline via local `webServer` in Playwright configs — no manual server, no accounts, no network:

```bash
npm test                          # vitest 39 component (with ErrorBoundary) — coverage 60%
npx playwright test                # E2E 13 flows — auto-starts vite on 5173
npx playwright test --config=playwright.a11y.config.ts   # a11y 11 axe
npx playwright test --config=playwright.visual.config.ts # visual regression (local screenshots)
npx playwright test --config=playwright.responsive.config.ts # 9 viewports 320→3840
```

First visual run creates baseline `tests/**/snapshots`; second run compares.

## ReUI

Registry: `@reui` — https://reui.io
Add components:
```bash
npx shadcn@latest add @reui/button @reui/data-grid @reui/dialog -o
```

## Observability

- `src/lib/logger.ts` — structured JSON logger (debug/info/warn/error) with `VITE_LOG_LEVEL`
- `src/components/ErrorBoundary.tsx` — catches render errors, logs via logger, shows fallback `role="alert"`

## Bridge to C++

Current viewport is canvas stub (`NullRenderer`). Integration options:
- Tauri: `npm create tauri-app` — bind Rust -> C++ via FFI
- Electron: `electron` + `node-ffi-napi` to `libspatial_cad`
- WASM: compile `engine/` with Emscripten -> `spatial.wasm`

For now uses mock data and talks to `apps/cli` via file `project.spatial`.
