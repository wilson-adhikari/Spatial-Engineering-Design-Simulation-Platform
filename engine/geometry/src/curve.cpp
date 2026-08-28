#include "geometry/curve.h"
#include <cmath>
namespace spatial::geometry{
math::Vec3 Arc::point(double t) const{ double a=start+(end-start)*t; return {center.x+radius*cos(a),center.y+radius*sin(a),center.z};}
math::Vec3 Arc::derivative(double t) const{ double a=start+(end-start)*t; double s=(end-start); return {-radius*sin(a)*s,radius*cos(a)*s,0};}
math::Vec3 Spline::point(double t) const{
 if(points.empty()) return {}; if(points.size()==1) return points[0];
 double scaled=t*(points.size()-1); int i=(int)scaled; if(i>= (int)points.size()-1) return points.back();
 double f=scaled-i; auto& a=points[i]; auto& b=points[i+1]; return {a.x+(b.x-a.x)*f,a.y+(b.y-a.y)*f,a.z+(b.z-a.z)*f};
}
}
