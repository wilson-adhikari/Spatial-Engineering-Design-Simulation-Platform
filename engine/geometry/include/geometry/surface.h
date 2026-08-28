#pragma once
#include "math/vec.h"
namespace spatial::geometry{
struct Surface{ virtual ~Surface()=default; virtual math::Vec3 point(double u,double v) const =0;};
struct PlaneSurface : Surface{ math::Vec3 origin{0,0,0},u{1,0,0},v{0,1,0}; math::Vec3 point(double uu,double vv) const override {return origin+u*uu+v*vv;}};
}
