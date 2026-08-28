#pragma once
#include "geometry/primitives.h"
#include "core/uuid.h"
namespace spatial::scene{
struct Mesh{
 core::Uuid id=core::Uuid::generate();
 geometry::MeshData data;
 std::string name;
 void set_data(geometry::MeshData d){ data=std::move(d);}
};
}
