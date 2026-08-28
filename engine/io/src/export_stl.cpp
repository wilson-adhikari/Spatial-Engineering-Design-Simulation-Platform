#include "io/formats.h"
#include <fstream>
namespace spatial::io{
bool export_stl(const geometry::MeshData& m,const std::string& path){
 std::ofstream f(path); if(!f) return false;
 f<<"solid spatial\n";
 for(size_t i=0;i+2<m.indices.size();i+=3){
  auto &a=m.vertices[m.indices[i]],&b=m.vertices[m.indices[i+1]],&c=m.vertices[m.indices[i+2]];
  auto n=(b-a).cross(c-a).normalized();
  f<<" facet normal "<<n.x<<" "<<n.y<<" "<<n.z<<"\n  outer loop\n";
  f<<"   vertex "<<a.x<<" "<<a.y<<" "<<a.z<<"\n";
  f<<"   vertex "<<b.x<<" "<<b.y<<" "<<b.z<<"\n";
  f<<"   vertex "<<c.x<<" "<<c.y<<" "<<c.z<<"\n  endloop\n endfacet\n";
 }
 f<<"endsolid\n"; return true;
}
bool export_obj(const geometry::MeshData& m,const std::string& path){
 std::ofstream f(path); if(!f) return false;
 for(auto& v:m.vertices) f<<"v "<<v.x<<" "<<v.y<<" "<<v.z<<"\n";
 for(size_t i=0;i+2<m.indices.size();i+=3) f<<"f "<<m.indices[i]+1<<" "<<m.indices[i+1]+1<<" "<<m.indices[i+2]+1<<"\n";
 return true;
}
geometry::MeshData import_stl(const std::string&){ return {};}
}
