# API Documentation

## C++ Engine (headers in `engine/*/include`)

### Core (`core/logger.h`, `result.h`, `uuid.h`, `event.h`, `command.h`)
```cpp
Logger::instance().log(LogLevel::Info, "msg");
Result<void> r = stack.execute(std::make_unique<CreatePartCommand>(part));
Uuid id = Uuid::generate();
EventBus::global().subscribe("input.click", [](void*){});
```

### Math (`math/vec.h`, `mat.h`, `quat.h`, `transform.h`)
```cpp
Vec3 a{1,0,0}, b{0,1,0}; auto c = a.cross(b).normalized();
Mat4 m = Mat4::translate({1,2,3}) * Mat4::perspective(fov, aspect, 0.1, 1000);
Quat q = Quat::from_axis_angle({0,0,1}, M_PI/2);
Transform t{{0,0,0}, q, {1,1,1}}; auto mat = t.matrix();
```

### Geometry (`geometry/primitives.h`)
```cpp
auto box = make_box({10,10,10});
auto cyl = make_cylinder(5,20,32);
auto sph = make_sphere(5,16,32);
```

### CAD (`cad/part.h`, `sketch.h`, `assembly.h`)
```cpp
auto part = std::make_shared<Part>();
auto sketch = part->create_sketch("XY");
sketch->add_circle({0,0}, 25);
sketch->add_constraint({ConstraintType::Equal, {}, 0});
part->extrude(sketch, 50);
auto mesh = part->build(); // MeshData
auto asm_ = std::make_shared<Assembly>(); asm_->add_part(part, {});
```

### IO (`io/project.h`, `formats.h`, `assets.h`)
```cpp
Project proj; proj.set_name("Robot"); proj.save("assets/models/example_project.spatial");
export_stl(mesh, "assets/models/out.stl");
auto mat = AssetLoader::load_material("assets/materials/steel.json");
```

### Simulation (`simulation/physics.h`, `solver.h`)
```cpp
PhysicsWorld w; w.add_body({{}, {}, {}, 10, false}); w.step(0.016);
```

## Python API (`python/api`)
```python
import spatial_py as spatial
project = spatial.create_project()
part = project.create_part()
sketch = part.create_sketch("XY")
sketch.circle(center=(0,0), radius=25)
part.extrude(sketch, distance=50)
project.save("robot_arm.part")
```

## Frontend ReUI (`apps/desktop/frontend/src`)
```tsx
import { ModelTree } from "@/components/ModelTree"
<ModelTree onSelect={id => console.log(id)} />
import { Viewport } from "@/components/Viewport"
<Viewport mode="shaded" />
import { Button } from "@/components/ui/button"
<Button variant="ghost" size="icon" aria-label="save"><Save/></Button>
```

## Rendering (`rendering/renderer.h`)
```cpp
auto r = create_renderer(Backend::OpenGL);
r->init(); r->begin_frame(); r->draw_scene(scene); r->end_frame();
```

## Doxygen
Generate: `doxygen Doxyfile` (see `docs/Doxyfile`). Output in `docs/html`.
