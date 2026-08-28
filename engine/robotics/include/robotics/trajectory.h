#pragma once
#include "math/vec.h"
#include <vector>
namespace spatial::robotics{
struct Waypoint{ math::Vec3 pos; double t=0;};
class Trajectory{
public:
 void add_waypoint(Waypoint w){ pts_.push_back(w);}
 math::Vec3 sample(double t) const;
private:
 std::vector<Waypoint> pts_;
};
}
