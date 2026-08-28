#include "io/project.h"
#include <fstream>
namespace spatial::io{
bool Project::save(const std::string& p){
 path=p; std::ofstream f(p); if(!f) return false;
 f<<"{\"name\":\""<<name<<"\", \"parts\":"<<parts.size()<<"}";
 return true;
}
bool Project::load(const std::string& p){ path=p; std::ifstream f(p); return (bool)f; }
void Project::autosave(){ if(!path.empty()) save(path+".autosave"); }
}
