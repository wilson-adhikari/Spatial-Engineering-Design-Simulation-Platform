#include "math/mat.h"
#include <cmath>
namespace spatial::math{
Mat4 Mat4::identity(){ Mat4 r{}; r.m={1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1}; return r;}
Mat4 Mat4::translate(Vec3 t){ auto r=identity(); r.m[12]=t.x; r.m[13]=t.y; r.m[14]=t.z; return r;}
Mat4 Mat4::scale(Vec3 s){ auto r=identity(); r.m[0]=s.x; r.m[5]=s.y; r.m[10]=s.z; return r;}
Mat4 Mat4::rotate_z(double rad){ auto r=identity(); double c=cos(rad),s=sin(rad); r.m[0]=c; r.m[1]=s; r.m[4]=-s; r.m[5]=c; return r;}
Mat4 Mat4::rotate_x(double rad){ auto r=identity(); double c=cos(rad),s=sin(rad); r.m[5]=c; r.m[6]=s; r.m[9]=-s; r.m[10]=c; return r;}
Mat4 Mat4::rotate_y(double rad){ auto r=identity(); double c=cos(rad),s=sin(rad); r.m[0]=c; r.m[2]=-s; r.m[8]=s; r.m[10]=c; return r;}
Mat4 Mat4::perspective(double fov,double aspect,double n,double f){
 double tan2=tan(fov*0.5); Mat4 r{}; r.m[0]=1/(aspect*tan2); r.m[5]=1/tan2; r.m[10]=-(f+n)/(f-n); r.m[11]=-1; r.m[14]=-2*f*n/(f-n); return r;}
Mat4 Mat4::orthographic(double l,double r,double b,double t,double n,double f){
 Mat4 m{}; m.m[0]=2/(r-l); m.m[5]=2/(t-b); m.m[10]=-2/(f-n); m.m[12]=-(r+l)/(r-l); m.m[13]=-(t+b)/(t-b); m.m[14]=-(f+n)/(f-n); m.m[15]=1; return m;}
Mat4 Mat4::look_at(Vec3 eye,Vec3 center,Vec3 up){
 Vec3 f=(center-eye).normalized(); Vec3 s=f.cross(up).normalized(); Vec3 u=s.cross(f);
 Mat4 r=identity(); r.m[0]=s.x; r.m[4]=s.y; r.m[8]=s.z; r.m[1]=u.x; r.m[5]=u.y; r.m[9]=u.z; r.m[2]=-f.x; r.m[6]=-f.y; r.m[10]=-f.z;
 r.m[12]=-s.dot(eye); r.m[13]=-u.dot(eye); r.m[14]=f.dot(eye); return r;}
Mat4 Mat4::operator*(const Mat4& o) const{
 Mat4 r{}; for(int i=0;i<4;i++) for(int j=0;j<4;j++){ double s=0; for(int k=0;k<4;k++) s+=m[k*4+i]*o.m[j*4+k]; r.m[j*4+i]=s;} return r;}
Vec4 Mat4::operator*(Vec4 v) const{
 return {m[0]*v.x+m[4]*v.y+m[8]*v.z+m[12]*v.w, m[1]*v.x+m[5]*v.y+m[9]*v.z+m[13]*v.w, m[2]*v.x+m[6]*v.y+m[10]*v.z+m[14]*v.w, m[3]*v.x+m[7]*v.y+m[11]*v.z+m[15]*v.w};}
Vec3 Mat4::transform_point(Vec3 p) const{ auto v=(*this)*Vec4{p.x,p.y,p.z,1}; return v.w!=0?Vec3{v.x/v.w,v.y/v.w,v.z/v.w}:Vec3{v.x,v.y,v.z};}
Vec3 Mat4::transform_vector(Vec3 v) const{ auto r=(*this)*Vec4{v.x,v.y,v.z,0}; return {r.x,r.y,r.z};}
}
