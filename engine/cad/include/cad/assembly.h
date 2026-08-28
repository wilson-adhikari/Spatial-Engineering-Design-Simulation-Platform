#pragma once
#include "cad/part.h"
#include "math/transform.h"
namespace spatial::cad{
enum class JointType{Fixed,Revolute,Prismatic,Cylindrical,Spherical,Planar};
struct Joint{ JointType type=JointType::Fixed; std::string name; core::Uuid a,b; math::Vec3 axis{0,0,1}; math::Vec3 origin{0,0,0}; double limits[2]={-3.14,3.14}; };
class Assembly{
public:
 core::Uuid id=core::Uuid::generate();
 std::string name="Assembly";
 struct Instance{ std::shared_ptr<Part> part; math::Transform xform; std::string name;};
 std::vector<Instance> instances;
 std::vector<Joint> joints;
 void add_part(std::shared_ptr<Part> p, math::Transform t={}){ instances.push_back({p,t,p->name});}
 void add_joint(Joint j){ joints.push_back(std::move(j));}
};
}
