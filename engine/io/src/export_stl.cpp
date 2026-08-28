#include "io/formats.h"
#include <fstream>
#include <filesystem>
#include <limits>
namespace fs = std::filesystem;
namespace spatial::io{
static bool safe_path(const std::string& p){
 if(p.empty()||p.size()>1024) return false;
 if(p.find("..")!=std::string::npos) return false;
 if(p.find('\0')!=std::string::npos) return false;
 fs::path path(p); if(path.is_absolute()) return false; return true;
}
bool export_stl(const geometry::MeshData& m,const std::string& path){
 if(!safe_path(path)) return false;
 if(m.vertices.size()>1000000 || m.indices.size()>3000000) return false;
 for(auto& v: m.vertices) if(!v.is_finite()) return false;
 for(auto idx: m.indices) if(idx >= m.vertices.size()) return false;
 try{
  fs::path p(path);
  if(p.has_parent_path()) fs::create_directories(p.parent_path());
  fs::path tmp = p; tmp += ".tmp";
  std::ofstream f(tmp);
  if(!f) return false;
  f<<"solid spatial\n";
  for(size_t i=0;i+2<m.indices.size();i+=3){
   auto &a=m.vertices[m.indices[i]],&b=m.vertices[m.indices[i+1]],&c=m.vertices[m.indices[i+2]];
   auto n=(b-a).cross(c-a);
   double len=n.length(); if(len>1e-12) n=n.normalized(); else n={0,0,0};
   if(!n.is_finite()) n={0,0,1};
   f<<" facet normal "<<n.x<<" "<<n.y<<" "<<n.z<<"\n  outer loop\n";
   f<<"   vertex "<<a.x<<" "<<a.y<<" "<<a.z<<"\n";
   f<<"   vertex "<<b.x<<" "<<b.y<<" "<<b.z<<"\n";
   f<<"   vertex "<<c.x<<" "<<c.y<<" "<<c.z<<"\n  endloop\n endfacet\n";
   if(f.tellp() > 200*1024*1024) return false;
  }
  f<<"endsolid\n"; f.close(); if(!f) return false;
  fs::rename(tmp, p);
  return true;
 } catch(...){ return false; }
}
bool export_obj(const geometry::MeshData& m,const std::string& path){
 if(!safe_path(path)) return false;
 if(m.vertices.size()>1000000) return false;
 for(auto& v: m.vertices) if(!v.is_finite()) return false;
 try{
  fs::path p(path);
  if(p.has_parent_path()) fs::create_directories(p.parent_path());
  fs::path tmp = p; tmp += ".tmp";
  std::ofstream f(tmp);
  if(!f) return false;
  for(auto& v:m.vertices) f<<"v "<<v.x<<" "<<v.y<<" "<<v.z<<"\n";
  for(size_t i=0;i+2<m.indices.size();i+=3) f<<"f "<<m.indices[i]+1<<" "<<m.indices[i+1]+1<<" "<<m.indices[i+2]+1<<"\n";
  f.close(); fs::rename(tmp, p); return true;
 } catch(...){ return false; }
}
geometry::MeshData import_stl(const std::string& path){
 if(!safe_path(path)) return {};
 try{
  fs::path p(path);
  if(!fs::exists(p)) return {};
  if(fs::file_size(p) > 200*1024*1024) return {};
  return {};
 } catch(...){ return {}; }
}
}
