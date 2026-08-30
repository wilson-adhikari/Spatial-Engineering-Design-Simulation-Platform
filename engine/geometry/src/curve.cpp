#include "geometry/curve.h"
#include <cmath>
#include <stdexcept>
namespace spatial::geometry{
math::Vec3 Arc::point(double t) const{
 if(!std::isfinite(t)) throw std::invalid_argument("t non-finite");
 if(!center.is_finite()||!std::isfinite(radius)||!std::isfinite(start)||!std::isfinite(end)) throw std::invalid_argument("arc non-finite");
 if(radius<=0||radius>1e6) throw std::invalid_argument("radius invalid");
 double a=start+(end-start)*t;
 if(!std::isfinite(a)) throw std::runtime_error("arc overflow");
 return {center.x+radius*cos(a),center.y+radius*sin(a),center.z};}
math::Vec3 Arc::derivative(double t) const{
 if(!std::isfinite(t)) throw std::invalid_argument("t non-finite");
 double a=start+(end-start)*t; double s=(end-start);
 if(!std::isfinite(a)||!std::isfinite(s)) throw std::runtime_error("arc derivative overflow");
 return {-radius*sin(a)*s,radius*cos(a)*s,0};}
math::Vec3 Spline::point(double t) const{
 if(!std::isfinite(t)) throw std::invalid_argument("t non-finite");
 if(points.empty()) return {};
 if(points.size()==1) return points[0];
 if(points.size()>10000) throw std::runtime_error("too many points");
 for(auto& p: points) if(!p.is_finite()) throw std::invalid_argument("point non-finite");
 double scaled=t*(points.size()-1); int i=(int)scaled; if(i>= (int)points.size()-1) return points.back();
 if(i<0) i=0;
 double f=scaled-i; if(!std::isfinite(f)) throw std::runtime_error("spline overflow");
 auto& a=points[i]; auto& b=points[i+1]; return {a.x+(b.x-a.x)*f,a.y+(b.y-a.y)*f,a.z+(b.z-a.z)*f};
}
}
