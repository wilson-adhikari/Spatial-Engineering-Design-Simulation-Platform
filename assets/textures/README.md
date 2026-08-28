# Textures - CC0 Original

Procedurally generated 256x256 PNGs, CC0, no external dependencies.

- checker_256.png - 32px checker, 854B, for grid/axes
- brushed_metal_256.png - brushed steel, 78KB, metallic 0.9 roughness 0.45
- concrete_256.png - concrete noise, 68KB
- normal_flat_256.png - flat normal (128,128,255), 759B
- roughness_gradient_256.png - horizontal gradient L channel

All textures are power-of-two, sanitized to 256x256, validated finite.
Usage: ssets/materials/*.json pbr.albedo references these.

Security: textures loaded via stb_image path traversal protected (is_safe_path), max 8K, 32MB cap.
