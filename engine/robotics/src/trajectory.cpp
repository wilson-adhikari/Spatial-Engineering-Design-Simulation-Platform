#include "robotics/trajectory.h"
#include <stdexcept>
namespace spatial::robotics{
math::Vec3 Trajectory::sample(double t) const{
 if(!std::isfinite(t)) return {};
 if(pts_.empty()) return {};
 if(pts_.size()==1) return pts_[0].pos;
 if(pts_.size()>10000) throw std::runtime_error("too many waypoints");
 for(size_t i=0;i+1<pts_.size();i++){
  if(!pts_[i].pos.is_finite()||!pts_[i+1].pos.is_finite()||!std::isfinite(pts_[i].t)||!std::isfinite(pts_[i+1].t)) continue;
  if(t>=pts_[i].t && t<=pts_[i+1].t){
   double denom = pts_[i+1].t-pts_[i].t;
   if(std::abs(denom)<1e-12) return pts_[i].pos;
   double a=(t-pts_[i].t)/denom;
   a=std::clamp(a,0.0,1.0);
   return pts_[i].pos*(1-a)+pts_[i+1].pos*a;
  }
 }
 return pts_.back().pos;
}
}
