#pragma once
#include "geometry/primitives.h"
#include <string>
namespace spatial::io{
bool export_stl(const geometry::MeshData& m, const std::string& path);
bool export_obj(const geometry::MeshData& m, const std::string& path);
geometry::MeshData import_stl(const std::string& path);
}
