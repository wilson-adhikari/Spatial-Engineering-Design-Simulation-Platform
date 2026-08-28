#pragma once
#include "math/vec.h"
#include "geometry/bbox.h"
#include <vector>
#include <cstdint>
namespace spatial::geometry{
struct MeshData{
 std::vector<math::Vec3> vertices;
 std::vector<uint32_t> indices;
 std::vector<math::Vec3> normals;
 BBox bbox;
 void compute_normals();
 void compute_bbox();
};
MeshData make_box(math::Vec3 size={1,1,1});
MeshData make_cylinder(double radius=1,double height=1,int segs=32);
MeshData make_sphere(double radius=1,int lat=16,int lon=32);
MeshData make_cone(double radius=1,double height=1,int segs=32);
MeshData make_torus(double major=1,double minor=0.3,int majSeg=32,int minSeg=16);
MeshData make_plane(double w=1,double h=1);
}

