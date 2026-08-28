#pragma once
#include "math/vec.h"
#include <string>
namespace spatial::rendering{
struct Material{
 std::string name="Default";
 math::Vec3 albedo{0.7,0.7,0.7};
 double metallic=0.0, roughness=0.5, opacity=1.0;
 bool wireframe=false;
};
}
