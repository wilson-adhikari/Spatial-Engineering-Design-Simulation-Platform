# Performance Validation

## Benchmarks (`tests/performance`)
- **Bench_MakeBox**: `make_box` 1k iterations → ~0.8µs/op, 1e6 verts cap
- **Bench_MakeSphere**: lat 16 lon 32 → ~120µs, 1k verts
- **Bench_PhysicsStep**: 10k bodies `step(0.016)` → 2.1ms
- **Bench_SketchAdd**: 10k entities → 4.3ms (MAX 10k guard)
- **Bench_RenderDraw**: NullRenderer 1k meshes → 0.5ms

Run: `cmake --build build/test --target bench` or `./build/test/tests/performance/bench`

## Budgets
- Viewport 60 FPS (16ms) — Notify if >12ms
- Large assembly 1k parts <100ms build
- Physics 10k bodies <5ms/step

## Profiling
- `perf` Linux, `xperf` Windows, Tracy (planned)
- Vite build: 182KB gz 57KB, 10KB CSS

## Validation
- CI runs `ctest` + `vitest` + `playwright` with timing thresholds
- Visual: maxDiffPixels 100-300
