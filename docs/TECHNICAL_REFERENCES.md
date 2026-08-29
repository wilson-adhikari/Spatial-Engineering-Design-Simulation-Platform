# Technical References

## Standards & Papers
- ISO 10303 STEP (AP214) — CAD exchange
- ISO 13584 PLIB — parts library
- OpenGL 4.6 Spec, Vulkan 1.3 Spec — rendering
- FEM: Zienkiewicz & Taylor — Finite Element Method
- Robotics: Craig — Introduction to Robotics (DH params, Jacobian)
- sRGB, PBR (Burley, Karis) — metallic/roughness

## Libraries
- React 18.3, Tailwind 3.4, Motion 12, Radix UI, ReUI (reui.io) — shadcn registry
- Playwright 1.45, Vitest 1.6, axe-core 4.10 — testing
- pybind11 (optional) — Python bindings
- stb_image (planned) — texture loading with is_safe_asset_path
- Eigen (future) — linear systems

## File Formats
- STL ASCII (`solid` + `facet normal` + `vertex`), OBJ (`v`/`f`/`mtllib`), .spatial (JSON `name/parts/version`), .mtl (Kd/Ks/Ns)

## Math
- Quat slerp: Shoemake 1985, Mat perspective: OpenGL, BBox numeric_limits

## Security
- OWASP ASVS 4.0, CWE-22 Path Traversal, CWE-789 Uncontrolled Mem Alloc, CWE-20 Input Validation
- CSP Level 3, WCAG 2.1 AA

## Assets
- Materials handbooks: MatWeb, ASM — densities/moduli in `assets/materials/*.json` (CC0 procedural)
- Textures: PIL 12.3 procedural 256x256 PNG
- Models: procedural make_box/cylinder/sphere (CC0)

## Build
- CMake 3.20+, C++20, Ninja, MSVC 2022, MinGW 14.2, Vite 5.4, Node 20.18
