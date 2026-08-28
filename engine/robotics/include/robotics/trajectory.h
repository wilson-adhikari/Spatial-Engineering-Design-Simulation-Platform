#pragma once
#include "math/vec.h"
#include <vector>
#include <algorithm>
namespace spatial::robotics{
struct Waypoint{ math::Vec3 pos; double t=0; bool is_valid() const { return pos.is_finite() && std::isfinite(t); } };
class Trajectory{
public:
 static constexpr size_t MAX_WP = 10000;
 bool add_waypoint(Waypoint w){
  if(!w.is_valid()) return false;
  if(pts_.size()>=MAX_WP) return false;
  pts_.push_back(w);
  return true;
 }
 math::Vec3 sample(double t) const;
 size_t size() const { return pts_.size(); }
private:
 std::vector<Waypoint> pts_;
};
}

