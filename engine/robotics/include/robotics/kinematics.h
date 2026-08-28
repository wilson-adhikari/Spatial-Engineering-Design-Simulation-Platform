#pragma once
#include "math/vec.h"
#include "math/mat.h"
#include <vector>
namespace spatial::robotics{
struct DHParam{ double a=0,alpha=0,d=0,theta=0; bool is_valid() const { return std::isfinite(a)&&std::isfinite(alpha)&&std::isfinite(d)&&std::isfinite(theta)&&std::abs(a)<1e6; } };
struct Joint{ double angle=0; double min=-3.14,max=3.14; DHParam dh; bool is_valid() const { return std::isfinite(angle)&&dh.is_valid()&&min<max; } };
class KinematicChain{
public:
 static constexpr size_t MAX_JOINTS = 32;
 bool add_joint(Joint j);
 math::Mat4 forward() const;
 bool inverse(math::Vec3 target, std::vector<double>& out);
 math::Mat4 jacobian() const;
 size_t size() const { return joints_.size(); }
private:
 std::vector<Joint> joints_;
};
}
