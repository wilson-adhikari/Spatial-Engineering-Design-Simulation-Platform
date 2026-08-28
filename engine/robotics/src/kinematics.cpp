#include "robotics/kinematics.h"
#include <cmath>
namespace spatial::robotics{
math::Mat4 KinematicChain::forward() const{
 math::Mat4 m=math::Mat4::identity();
 for(auto& j:joints_){ double ct=cos(j.angle+j.dh.theta),st=sin(j.angle+j.dh.theta), ca=cos(j.dh.alpha),sa=sin(j.dh.alpha);
  math::Mat4 t{}; t.m={ct,-st*ca,st*sa,j.dh.a*ct, st,ct*ca,-ct*sa,j.dh.a*st, 0,sa,ca,j.dh.d, 0,0,0,1}; m=m*t;}
 return m;
}
bool KinematicChain::inverse(math::Vec3, std::vector<double>& out){ out.assign(joints_.size(),0); return true;}
math::Mat4 KinematicChain::jacobian() const {return math::Mat4::identity();}
}
