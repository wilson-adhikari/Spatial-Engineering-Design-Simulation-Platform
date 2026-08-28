#include "math/quat.h"
#include "math/mat.h"
#include <cmath>
namespace spatial::math{
Quat Quat::from_axis_angle(Vec3 axis,double rad){
 auto n=axis.normalized(); double s=sin(rad*0.5); return {n.x*s,n.y*s,n.z*s,cos(rad*0.5)};}
Quat Quat::from_euler(double roll,double pitch,double yaw){
 double cr=cos(roll*0.5),sr=sin(roll*0.5),cp=cos(pitch*0.5),sp=sin(pitch*0.5),cy=cos(yaw*0.5),sy=sin(yaw*0.5);
 return {sr*cp*cy-cr*sp*sy, cr*sp*cy+sr*cp*sy, cr*cp*sy-sr*sp*cy, cr*cp*cy+sr*sp*sy};}
Quat Quat::normalized() const{ double l=sqrt(x*x+y*y+z*z+w*w); return {x/l,y/l,z/l,w/l};}
Quat Quat::operator*(Quat o) const{
 return {w*o.x+x*o.w+y*o.z-z*o.y, w*o.y-x*o.z+y*o.w+z*o.x, w*o.z+x*o.y-y*o.x+z*o.w, w*o.w-x*o.x-y*o.y-z*o.z};}
Quat Quat::slerp(Quat o,double t) const{
 double dot=x*o.x+y*o.y+z*o.z+w*o.w; if(dot<0){o={-o.x,-o.y,-o.z,-o.w}; dot=-dot;}
 if(dot>0.9995) return {(1-t)*x+t*o.x,(1-t)*y+t*o.y,(1-t)*z+t*o.z,(1-t)*w+t*o.w};
 double th=acos(dot), s=sin(th); return {(sin((1-t)*th)/s)*x + (sin(t*th)/s)*o.x, (sin((1-t)*th)/s)*y + (sin(t*th)/s)*o.y, (sin((1-t)*th)/s)*z + (sin(t*th)/s)*o.z, (sin((1-t)*th)/s)*w + (sin(t*th)/s)*o.w};}
Mat4 Quat::to_mat4() const{
 double xx=x*x,yy=y*y,zz=z*z,xy=x*y,xz=x*z,yz=y*z,wx=w*x,wy=w*y,wz=w*z;
 Mat4 m=Mat4::identity(); m.m[0]=1-2*(yy+zz); m.m[1]=2*(xy+wz); m.m[2]=2*(xz-wy);
 m.m[4]=2*(xy-wz); m.m[5]=1-2*(xx+zz); m.m[6]=2*(yz+wx); m.m[8]=2*(xz+wy); m.m[9]=2*(yz-wx); m.m[10]=1-2*(xx+yy); return m;}
}
