import spatial_py as spatial
import re
def validate_path(p):
    if ".." in p or len(p)>256 or not re.match(r"^[a-zA-Z0-9_\-\.\/]+$", p): raise ValueError("invalid path")
    return p

project = spatial.create_project()
part = project.create_part()
sketch = part.create_sketch("XY")
if sketch is None: raise RuntimeError("sketch failed")
sketch.circle(center=(0, 0), radius=25)
part.extrude(sketch, distance=50)
validate_path("robot_arm.part")
project.save("robot_arm.part")
print("Created robot_arm.part")

