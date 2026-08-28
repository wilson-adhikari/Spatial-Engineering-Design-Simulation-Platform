#pragma once
#include <cmath>
#include <array>
namespace spatial::math{
struct Vec2{ double x=0,y=0; Vec2 operator+(Vec2 o) const {return {x+o.x,y+o.y};}
 Vec2 operator-(Vec2 o) const {return {x-o.x,y-o.y};}
 Vec2 operator*(double s) const {return {x*s,y*s};}
 double dot(Vec2 o) const {return x*o.x+y*o.y;}
 double length() const {return std::sqrt(x*x+y*y);}
 Vec2 normalized() const {double l=length(); return l>1e-12? Vec2{x/l,y/l}:Vec2{};}
};
struct Vec3{ double x=0,y=0,z=0;
 Vec3 operator+(Vec3 o) const {return {x+o.x,y+o.y,z+o.z};}
 Vec3 operator-(Vec3 o) const {return {x-o.x,y-o.y,z-o.z};}
 Vec3 operator*(double s) const {return {x*s,y*s,z*s};}
 Vec3 operator/(double s) const {return {x/s,y/s,z/s};}
 double dot(Vec3 o) const {return x*o.x+y*o.y+z*o.z;}
 Vec3 cross(Vec3 o) const {return {y*o.z-z*o.y, z*o.x-x*o.z, x*o.y-y*o.x};}
 double length() const {return std::sqrt(x*x+y*y+z*z);}
 Vec3 normalized() const {double l=length(); return l>1e-12? Vec3{x/l,y/l,z/l}:Vec3{};}
};
struct Vec4{ double x=0,y=0,z=0,w=0;};
}
