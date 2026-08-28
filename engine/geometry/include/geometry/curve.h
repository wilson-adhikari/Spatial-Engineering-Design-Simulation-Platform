#pragma once
#include "math/vec.h"
#include <vector>
namespace spatial::geometry{
struct Curve{
 virtual ~Curve()=default;
 virtual math::Vec3 point(double t) const =0;
 virtual math::Vec3 derivative(double t) const =0;
};
struct Line : Curve{ math::Vec3 p0,p1; math::Vec3 point(double t) const override {return {p0.x+(p1.x-p0.x)*t,p0.y+(p1.y-p0.y)*t,p0.z+(p1.z-p0.z)*t};}
 math::Vec3 derivative(double) const override {return p1-p0;}};
struct Arc : Curve{ math::Vec3 center; double radius=1,start=0,end=6.28318; bool ccw=true;
 math::Vec3 point(double t) const override; math::Vec3 derivative(double t) const override;};
struct Spline : Curve{ std::vector<math::Vec3> points; math::Vec3 point(double t) const override; math::Vec3 derivative(double) const override {return {0,0,0};}
};
}
