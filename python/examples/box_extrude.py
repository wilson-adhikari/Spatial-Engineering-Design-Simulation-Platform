import spatial_py as spatial

project = spatial.create_project()
part = project.create_part()
sketch = part.create_sketch(""XY"")
sketch.line((0,0),(50,0))
sketch.line((50,0),(50,50))
sketch.line((50,50),(0,50))
sketch.line((0,50),(0,0))
part.extrude(sketch, distance=20)
project.save(""box.part"")
