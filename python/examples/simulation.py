import spatial_py as spatial

project = spatial.create_project()
part = project.create_part()
sketch = part.create_sketch(""XY"")
sketch.circle((0,0), 10)
part.extrude(sketch, 100)
print(""Run FEA..."")
# future: result = spatial.simulation.fea(part, material=""Steel"", load=1000)
# spatial.visualize(result, mode=""stress"")
