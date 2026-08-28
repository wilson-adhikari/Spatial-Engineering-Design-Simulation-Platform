#include "math/transform.h"
namespace spatial::math{
Mat4 Transform::matrix() const{
 auto t=Mat4::translate(position);
 auto r=rotation.to_mat4();
 auto s=Mat4::scale(scale);
 return t*r*s;
}
Transform Transform::from_matrix(const Mat4&){ return {};}
Transform Transform::operator*(const Transform& o) const{
 Transform r; r.position=apply(o.position); r.rotation=(rotation*o.rotation).normalized(); r.scale={scale.x*o.scale.x,scale.y*o.scale.y,scale.z*o.scale.z}; return r;}
Vec3 Transform::apply(Vec3 p) const{ return rotation.to_mat4().transform_vector({p.x*scale.x,p.y*scale.y,p.z*scale.z})+position;}
}
