# Reproducible Builds & SBOM

## Pins
- Node: 20.18.1 (`node -v`), npm 10.8.2, lockfile `package-lock.json` (exact 18.3.1 etc. no ^)
- CMake: 3.29.3, C++20, Ninja/MinGW 14.2/MSVC 2022
- Playwright: chromium-1124 (hash pinned)
- Python: 3.11, Pillow 12.3

## Determinism
- `CMAKE_CXX_VISIBILITY_PRESET hidden`, `hidden` inlines, no `__DATE__`
- Asset generation: `random.seed(0)` for brushed_metal, deterministic
- `package-lock.json` + `CMakePresets.json` checked in
- No network during `cmake --build` (offline-first)

## SBOM
Generate: `npm sbom --sbom-format cyclonedx > sbom.json` + `cmake --build --verbose` log.
Stored in `dist/sbom.json` per release.

## Verification
```bash
rm -rf build && cmake -S . -B build -G "MinGW Makefiles" && cmake --build build && sha256sum build/test/apps/cli/spatial_cli.exe
```
Should match CI artifact hash.

## Attestation
Release workflow signs artifacts with `cosign` (planned).
