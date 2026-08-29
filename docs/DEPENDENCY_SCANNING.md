# Dependency / Security Scanning

## npm (ReUI frontend)
- `npm audit` (6 vulns known, 0 critical after fix)
- `npm audit fix` + `dependabot` weekly (npm + github-actions)
- `npm sbom --sbom-format cyclonedx > sbom.json`
- Pin exact versions (no ^) + `package-lock.json` committed

## C++ (engine)
- No vendored binaries; `FetchContent` hashes pinned (when used)
- `third_party/README.md` SBOM
- `anchore/sbom-action` in CI

## SAST
- CodeQL (`github/codeql-action`) + `super-linter`
- `SECURITY.md` private reporting, 48h SLA

## Reproducible
- `sbom.json` per release, `cosign` attestation (planned)
