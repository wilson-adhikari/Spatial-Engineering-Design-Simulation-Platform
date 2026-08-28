#pragma once
#include "math/vec.h"
#include <array>
namespace spatial::math{
struct Mat4{
 std::array<double,16> m{};
 static Mat4 identity();
 static Mat4 translate(Vec3 t);
 static Mat4 scale(Vec3 s);
 static Mat4 rotate_x(double rad);
 static Mat4 rotate_y(double rad);
 static Mat4 rotate_z(double rad);
 static Mat4 perspective(double fov_rad,double aspect,double near_,double far_);
 static Mat4 orthographic(double l,double r,double b,double t,double n,double f);
 static Mat4 look_at(Vec3 eye,Vec3 center,Vec3 up);
 Mat4 operator*(const Mat4& o) const;
 Vec4 operator*(Vec4 v) const;
 Vec3 transform_point(Vec3 p) const;
 Vec3 transform_vector(Vec3 v) const;
 double* data(){return m.data();}
 const double* data() const {return m.data();}
};
}
