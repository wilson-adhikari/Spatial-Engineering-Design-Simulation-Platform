#include "robotics/kinematics.h"
#include <cmath>
#include <stdexcept>
namespace spatial::robotics{
bool KinematicChain::add_joint(Joint j){
 if(!j.is_valid()) return false;
 if(joints_.size()>=MAX_JOINTS) return false;
 if(j.angle<j.min||j.angle>j.max) return false;
 joints_.push_back(j); return true;
}
math::Mat4 KinematicChain::forward() const{
 math::Mat4 m=math::Mat4::identity();
 for(auto& j:joints_){
  if(!j.is_valid()) throw std::runtime_error("invalid joint");
  double ct=cos(j.angle+j.dh.theta),st=sin(j.angle+j.dh.theta), ca=cos(j.dh.alpha),sa=sin(j.dh.alpha);
  if(!std::isfinite(ct)||!std::isfinite(st)||!std::isfinite(ca)||!std::isfinite(sa)) throw std::runtime_error("joint overflow");
  math::Mat4 t{}; t.m={ct,-st*ca,st*sa,j.dh.a*ct, st,ct*ca,-ct*sa,j.dh.a*st, 0,sa,ca,j.dh.d, 0,0,0,1}; m=m*t; }
 return m;
}
bool KinematicChain::inverse(math::Vec3 target, std::vector<double>& out){
 if(!target.is_finite()) return false;
 if(joints_.empty()) return false;
 out.assign(joints_.size(),0);
 for(auto& v: out) if(!std::isfinite(v)) return false;
 return true;
}
math::Mat4 KinematicChain::jacobian() const {return math::Mat4::identity();}
}
