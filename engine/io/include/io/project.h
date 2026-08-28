#pragma once
#include "cad/part.h"
#include "cad/assembly.h"
#include <string>
namespace spatial::io{
struct Project{
 std::string name="Untitled";
 std::string path;
 std::vector<std::shared_ptr<cad::Part>> parts;
 std::vector<std::shared_ptr<cad::Assembly>> assemblies;
 static constexpr size_t MAX_NAME_LEN = 256;
 static constexpr size_t MAX_PARTS = 10000;
 bool save(const std::string& p);
 bool load(const std::string& p);
 void autosave();
 bool set_name(const std::string& n){
  if(n.empty()||n.size()>MAX_NAME_LEN) return false;
  for(char c: n) if(c=='\0') return false;
  name=n; return true;
 }
};
}
