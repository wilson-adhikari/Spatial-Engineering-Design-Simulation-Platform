# Security Policy

## Reporting
Report vulnerabilities to security@spatial.local (do not open public issues).
We aim to respond within 48h.

## Hardening Applied (2026-08-28 audit)

### C++ Core
- BBox uses numeric_limits, finite checks, is_valid()
- Vec/Quat normalized guards divide-by-zero, NaN, infinite
- Geometry primitives validate radius/segs bounds, DoS limits (100k verts), OOB checks
- LinearArena bounded, thread-safe, no leak, RAII
- Uuid: mutex, random_device with seed_seq + fallback counter, not predictable
- CommandStack: mutex, MAX_STACK 1000, null check, rollback on undo fail
- Sketch: MAX_ENTITIES/CONSTRAINTS 10k, finite checks, plane allowlist

### IO / Filesystem
- Path traversal blocked: rejects `..`, absolute paths, null bytes, size>1024
- Restricts to relative paths, creates parent dirs safely
- Atomic write via .tmp + rename, file size caps (100MB project, 200MB STL)
- Index bounds validated, finite vertex check, overwrite protection

### Simulation / Physics
- step() validates dt (0,1], gravity finite, mass>1e-9, MAX_BODIES 10k
- NaN/infinite recovery, force reset

### Scripting
- Disabled by default (`enabled_=false`), permission bitmask (FileRead etc.)
- Path allowlist, code blocklist (os/subprocess/eval), MAX_CODE 1MB, timeouts

### Hardware
- DeviceManager mutex, id length 256, permission gate `request_permission`

### CLI
- Allowlist args, length 64, rejects injection, try/catch, set_name validation

### Frontend ReUI
- CSP meta (default-src self), Vite host 127.0.0.1, no CORS, no sourcemap
- Deps pinned exact versions, @radix-ui/* corrected, motion 12, eslint-security
- ModelTree sanitizeId regex, no innerHTML

### Build
- -Wall -Wextra -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -z RelRO,Now,noexecstack
- MSVC /guard:cf /sdl /DYNAMICBASE /NXCOMPAT
- Optional ASan/UBSan (`-DSPATIAL_ENABLE_SANITIZERS=ON`)
- .gitignore blocks .env, *.key, secrets/

## Remaining Recommendations
- Enable OS code signing, sandbox Python via RestrictedPython or WASM
- Fuzz geometry/tessellation with libFuzzer
- Add SAST (CodeQL) + Dependabot + npm audit in CI

