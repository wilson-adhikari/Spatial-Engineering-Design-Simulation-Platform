#include "robotics/trajectory.h"
namespace spatial::robotics{
math::Vec3 Trajectory::sample(double t) const{
 if(pts_.empty()) return {}; if(pts_.size()==1) return pts_[0].pos;
 for(size_t i=0;i+1<pts_.size();i++) if(t>=pts_[i].t && t<=pts_[i+1].t){
  double a=(t-pts_[i].t)/(pts_[i+1].t-pts_[i].t); return pts_[i].pos*(1-a)+pts_[i+1].pos*a;}
 return pts_.back().pos;
}
}
