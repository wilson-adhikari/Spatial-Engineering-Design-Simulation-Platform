#pragma once
#include "math/vec.h"
#include <algorithm>
#include <limits>
namespace spatial::geometry{
struct BBox{
 math::Vec3 min{std::numeric_limits<double>::max(),std::numeric_limits<double>::max(),std::numeric_limits<double>::max()};
 math::Vec3 max{std::numeric_limits<double>::lowest(),std::numeric_limits<double>::lowest(),std::numeric_limits<double>::lowest()};
 void expand(math::Vec3 p){ min.x=std::min(min.x,p.x); min.y=std::min(min.y,p.y); min.z=std::min(min.z,p.z); max.x=std::max(max.x,p.x); max.y=std::max(max.y,p.y); max.z=std::max(max.z,p.z);}
 math::Vec3 center() const {return {(min.x+max.x)*0.5,(min.y+max.y)*0.5,(min.z+max.z)*0.5};}
 math::Vec3 size() const {return {max.x-min.x,max.y-min.y,max.z-min.z};}
 bool is_valid() const { return min.x<=max.x && min.y<=max.y && min.z<=max.z; }
 bool contains(math::Vec3 p) const {return p.x>=min.x&&p.x<=max.x&&p.y>=min.y&&p.y<=max.y&&p.z>=min.z&&p.z<=max.z;}
 bool intersects(const BBox& o) const {return !(max.x<o.min.x||min.x>o.max.x||max.y<o.min.y||min.y>o.max.y||max.z<o.min.z||min.z>o.max.z);}
 double volume() const { if(!is_valid()) return 0; auto s=size(); return s.x*s.y*s.z; }
};
struct Ray{ math::Vec3 origin,dir; bool is_normalized() const { auto l=dir.length(); return l>0.999 && l<1.001; } };
struct Plane{ math::Vec3 normal{0,1,0}; double d=0; bool is_normalized() const { auto l=normal.length(); return l>0.999 && l<1.001; } double distance(math::Vec3 p) const {return normal.dot(p)-d;}};
}

