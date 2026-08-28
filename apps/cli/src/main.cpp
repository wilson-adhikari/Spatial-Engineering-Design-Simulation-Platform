#include "io/project.h"
#include "cad/primitives.h"
#include "io/formats.h"
#include <iostream>
#include <string>
#include <unordered_set>
int main(int argc,char** argv){
 std::cout<<"Spatial CLI v0.1.0\n";
 std::unordered_set<std::string> allowed = {"--create-box","--help","--version"};
 for(int i=1;i<argc;i++){
  std::string arg(argv[i]);
  if(arg.size()>64){ std::cerr<<"arg too long\n"; return 1; }
  if(arg.rfind("--",0)!=0){ std::cerr<<"invalid arg: "<<arg.substr(0,16)<<"\n"; return 1; }
  if(allowed.find(arg)==allowed.end()){ std::cerr<<"unknown arg\n"; return 1; }
  if(arg=="--help"){ std::cout<<"Usage: spatial_cli [--create-box] [--help] [--version]\n"; return 0; }
  if(arg=="--version"){ std::cout<<"0.1.0\n"; return 0; }
  if(arg=="--create-box"){
   try{
    auto p=spatial::cad::make_box_part(10,20,30);
    auto m=p->build();
    if(!spatial::io::export_stl(m, "box.stl")){ std::cerr<<"export failed\n"; return 1; }
    std::cout<<"Created box.stl with "<<m.vertices.size()<<" verts\n";
   } catch(const std::exception& e){ std::cerr<<"error: "<<e.what()<<"\n"; return 1; }
  }
 }
 try{
  spatial::io::Project proj;
  if(!proj.set_name("CLIProject")) return 1;
  if(!proj.save("project.spatial")){ std::cerr<<"save failed\n"; return 1; }
  std::cout<<"Saved project.spatial\n";
 } catch(const std::exception& e){ std::cerr<<"save error\n"; return 1; }
 return 0;
}
