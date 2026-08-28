#pragma once
#include "math/vec.h"
namespace spatial::math{
struct Quat{ double x=0,y=0,z=0,w=1;
 static Quat identity(){return {};}
 static Quat from_axis_angle(Vec3 axis,double rad);
 static Quat from_euler(double roll,double pitch,double yaw);
 Quat normalized() const;
 Quat operator*(Quat o) const;
 Quat slerp(Quat o,double t) const;
 struct Mat4 to_mat4() const;
};
}
