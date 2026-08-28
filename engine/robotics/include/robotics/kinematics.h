#pragma once
#include "math/vec.h"
#include "math/mat.h"
#include <vector>
namespace spatial::robotics{
struct DHParam{ double a=0,alpha=0,d=0,theta=0;};
struct Joint{ double angle=0; double min=-3.14,max=3.14; DHParam dh;};
class KinematicChain{
public:
 void add_joint(Joint j){ joints_.push_back(j);}
 math::Mat4 forward() const;
 bool inverse(math::Vec3 target, std::vector<double>& out);
 math::Mat4 jacobian() const;
private:
 std::vector<Joint> joints_;
};
}
