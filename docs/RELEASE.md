# Release Management

## Versioning (SemVer)
- `0.1.0` MVP, `0.2.0` assets+hardening, `0.3.0` ReUI heavy tests
- Tag: `git tag v0.x.y && git push origin v0.x.y`

## Changelog
See `CHANGELOG.md` (Keep a Changelog). Update per PR.

## Process
1. `npm version patch/minor/major` + `cmake -S . -B build`
2. `ctest && npx vitest run && npx playwright test`
3. `npm run build` + `cmake --build build/release`
4. `gh release create v0.x.y --generate-notes` + artifacts (`spatial_cli.exe`, `dist.zip`, `sbom.json`)

## Artifacts
- `spatial_desktop` (ReUI frontend `dist/` + C++ `spatial_desktop.exe`)
- `spatial_cli` + `box.stl` example
- `assets/` (CC0)

## CI Release
`.github/workflows/ci.yml` → `release` job on tag `v*` publishes to GitHub Releases.

## Long-term
Stage roadmap in `docs/ROADMAP.md`, milestones quarterly.
