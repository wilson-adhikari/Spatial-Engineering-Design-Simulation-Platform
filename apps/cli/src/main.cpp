#include "io/project.h"
#include "cad/primitives.h"
#include "io/formats.h"
#include <iostream>
int main(int argc,char** argv){
 std::cout<<"Spatial CLI v0.1.0\n";
 if(argc>1 && std::string(argv[1])=="--create-box"){
  auto p=spatial::cad::make_box_part(10,20,30);
  auto m=p->build();
  spatial::io::export_stl(m, "box.stl");
  std::cout<<"Created box.stl with "<<m.vertices.size()<<" verts\n";
 }
 spatial::io::Project proj; proj.name="CLIProject"; proj.save("project.spatial");
 std::cout<<"Saved project.spatial\n";
 return 0;
}
