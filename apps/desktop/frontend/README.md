# Spatial Desktop — ReUI

React + Tailwind + ReUI (shadcn registry) frontend for the C++ Spatial Engine.

## Install (requires Node 18+)

```powershell
# install Node via https://nodejs.org then:
cd apps/desktop/frontend
npm install
npm run dev      # http://localhost:5173
npm run build
```

## ReUI

Registry: `@reui` — https://reui.io
Add components:
```bash
npx shadcn@latest add @reui/button @reui/data-grid @reui/dialog -o
```

## Bridge to C++

Current viewport is canvas stub (`NullRenderer`). Integration options:
- Tauri: `npm create tauri-app` — bind Rust -> C++ via FFI
- Electron: `electron` + `node-ffi-napi` to `libspatial_cad`
- WASM: compile `engine/` with Emscripten -> `spatial.wasm`

For now uses mock data and talks to `apps/cli` via file `project.spatial`.

