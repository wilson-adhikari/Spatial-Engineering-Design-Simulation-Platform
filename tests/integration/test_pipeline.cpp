#include "cad/part.h"
#include "cad/primitives.h"
#include "scene/scene.h"
#include "io/project.h"
#include <cassert>
#include <iostream>
int main(){
 spatial::io::Project proj; proj.name="Integration";
 auto part=spatial::cad::make_box_part(5,5,5);
 proj.parts.push_back(part);
 spatial::scene::Mesh m; m.data=part->build();
 assert(!m.data.vertices.empty());
 bool ok=proj.save("test.spatial");
 assert(ok);
 std::cout<<"integration pipeline passed\n";
 return 0;
}

