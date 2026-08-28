import spatial_py as spatial

project = spatial.create_project()
part = project.create_part()
sketch = part.create_sketch(""XY"")
sketch.circle(center=(0, 0), radius=25)
part.extrude(sketch, distance=50)
project.save(""robot_arm.part"")
print(""Created robot_arm.part"")
