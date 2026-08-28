#pragma once
#include "math/vec.h"
#include "math/mat.h"
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
namespace spatial::scene{
enum class Projection{Perspective,Orthographic};
struct Camera{
 math::Vec3 position{0,2,5}, target{0,0,0}, up{0,1,0};
 double fov=60*M_PI/180, aspect=16.0/9, near_=0.1, far_=1000;
 Projection proj=Projection::Perspective;
 math::Mat4 view_matrix() const {return math::Mat4::look_at(position,target,up);}
 math::Mat4 proj_matrix() const {return proj==Projection::Perspective? math::Mat4::perspective(fov,aspect,near_,far_) : math::Mat4::orthographic(-5,5,-5,5,near_,far_);}
};
}

