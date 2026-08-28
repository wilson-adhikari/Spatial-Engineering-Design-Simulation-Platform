# Models - CC0 Original

All models are original procedural geometry, CC0.

- primitive_box.stl/obj - 10x10x10 box, 12 tris, steel
- primitive_cylinder.stl - r5 h20, 32 tris
- primitive_sphere.stl - r5, lat8 lon16
- bracket.stl - L-bracket 40x40x5
- robot_arm_link.stl - robot arm link (box)
- assembly.obj - 2-box assembly with steel/aluminum
- example_project.spatial - native project referencing library.json

Import via: spatial_cli --import assets/models/primitive_box.stl
Export via io::export_stl(mesh, "out.stl") with path traversal protection.
