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
 bool save(const std::string& p);
 bool load(const std::string& p);
 void autosave();
};
}
