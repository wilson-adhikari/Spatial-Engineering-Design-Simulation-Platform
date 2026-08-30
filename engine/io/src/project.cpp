#include "io/project.h"
#include <fstream>
#include <filesystem>
#include <limits>
namespace fs = std::filesystem;
namespace spatial::io{
static bool is_safe_path(const std::string& p){
 if(p.empty()||p.size()>1024) return false;
 if(p.find('\0')!=std::string::npos) return false;
 if(p.find("..")!=std::string::npos) return false;
 fs::path path(p);
 if(path.is_absolute()) return false;
 for(auto& part: path){ auto s=part.string(); if(s==".."||s=="." ) return false; }
 return true;
}
static constexpr size_t MAX_PROJECT_BYTES = 100 * 1024 * 1024;
bool Project::save(const std::string& p){
 if(!is_safe_path(p)) return false;
 if(name.size()>256) return false;
 if(parts.size()>10000||assemblies.size()>10000) return false;
 try{
  fs::path path(p);
  if(path.has_parent_path()) fs::create_directories(path.parent_path());
  fs::path tmp = path; tmp += ".tmp";
  std::ofstream f(tmp, std::ios::binary);
  if(!f) return false;
  f<<"{\"name\":\""<<name<<"\", \"parts\":"<<parts.size()<<", \"version\":1}";
  if(f.tellp() > (std::streampos)MAX_PROJECT_BYTES) return false;
  f.close();
  if(!f) return false;
  fs::rename(tmp, path);
  this->path=p;
  return true;
 } catch(...){ return false; }
}
bool Project::load(const std::string& p){
 if(!is_safe_path(p)) return false;
 try{
  fs::path path(p);
  if(!fs::exists(path)) return false;
  if(fs::file_size(path) > MAX_PROJECT_BYTES) return false;
  std::ifstream f(path, std::ios::binary);
  if(!f) return false;
  char buf[1024]={0};
  f.read(buf, sizeof(buf)-1);
  this->path=p;
  return (bool)f || f.gcount()>0;
 } catch(...){ return false; }
}
void Project::autosave(){
 if(path.empty()||!is_safe_path(path)) return;
 try{ save(path+".autosave"); } catch(...){}
}
}

