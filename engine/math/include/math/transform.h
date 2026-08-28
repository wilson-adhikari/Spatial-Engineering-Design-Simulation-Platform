#pragma once
#include "math/vec.h"
#include "math/quat.h"
#include "math/mat.h"
namespace spatial::math{
struct Transform{
 Vec3 position{0,0,0};
 Quat rotation{};
 Vec3 scale{1,1,1};
 Mat4 matrix() const;
 static Transform from_matrix(const Mat4& m);
 Transform operator*(const Transform& o) const;
 Vec3 apply(Vec3 p) const;
};
}
