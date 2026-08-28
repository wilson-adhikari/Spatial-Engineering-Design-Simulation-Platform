#include "geometry/primitives.h"
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
namespace spatial::geometry{
void MeshData::compute_bbox(){ bbox={}; for(auto& v:vertices) bbox.expand(v);}
void MeshData::compute_normals(){ normals.assign(vertices.size(),{0,0,0}); for(size_t i=0;i+2<indices.size();i+=3){
 auto &a=vertices[indices[i]],&b=vertices[indices[i+1]],&c=vertices[indices[i+2]]; auto n=(b-a).cross(c-a).normalized();
 normals[indices[i]]=normals[indices[i]]+n; normals[indices[i+1]]=normals[indices[i+1]]+n; normals[indices[i+2]]=normals[indices[i+2]]+n;}
 for(auto& n:normals) n=n.normalized(); }

MeshData make_box(math::Vec3 s){
 MeshData m; double hx=s.x*0.5,hy=s.y*0.5,hz=s.z*0.5;
 m.vertices={{-hx,-hy,-hz},{hx,-hy,-hz},{hx,hy,-hz},{-hx,hy,-hz},{-hx,-hy,hz},{hx,-hy,hz},{hx,hy,hz},{-hx,hy,hz}};
 m.indices={0,1,2,0,2,3,4,6,5,4,7,6,0,4,5,0,5,1,2,5,6,2,6,7,0,3,7,0,7,4,1,5,6,1,6,2};
 m.compute_normals(); m.compute_bbox(); return m;}

MeshData make_plane(double w,double h){ MeshData m; double hw=w*0.5,hh=h*0.5;
 m.vertices={{-hw,0,-hh},{hw,0,-hh},{hw,0,hh},{-hw,0,hh}}; m.indices={0,1,2,0,2,3}; m.compute_normals(); m.compute_bbox(); return m;}

MeshData make_cylinder(double r,double h,int segs){
 MeshData m; double hh=h*0.5;
 for(int i=0;i<segs;i++){ double a=2*M_PI*i/segs; double x=cos(a)*r,z=sin(a)*r;
  m.vertices.push_back({x,-hh,z}); m.vertices.push_back({x,hh,z});}
 for(int i=0;i<segs;i++){ int a=i*2,b=((i+1)%segs)*2,c=b+1,d=a+1; m.indices.insert(m.indices.end(),{ (uint32_t)a,(uint32_t)b,(uint32_t)c, (uint32_t)a,(uint32_t)c,(uint32_t)d});}
 m.compute_normals(); m.compute_bbox(); return m;}

MeshData make_sphere(double rad,int lat,int lon){
 MeshData m;
 for(int i=0;i<=lat;i++){ double v=(double)i/lat, phi=v*M_PI; for(int j=0;j<=lon;j++){ double u=(double)j/lon, th=u*2*M_PI;
  m.vertices.push_back({rad*sin(phi)*cos(th), rad*cos(phi), rad*sin(phi)*sin(th)});}}
 for(int i=0;i<lat;i++) for(int j=0;j<lon;j++){ int a=i*(lon+1)+j,b=a+lon+1; m.indices.insert(m.indices.end(),{ (uint32_t)a,(uint32_t)b,(uint32_t)a+1, (uint32_t)b,(uint32_t)b+1,(uint32_t)a+1});}
 m.compute_normals(); m.compute_bbox(); return m;}

MeshData make_cone(double r,double h,int segs){
 MeshData m; double hh=h*0.5; m.vertices.push_back({0,hh,0});
 for(int i=0;i<segs;i++){ double a=2*M_PI*i/segs; m.vertices.push_back({cos(a)*r,-hh,sin(a)*r});}
 for(int i=0;i<segs;i++){ int a=0,b=1+i,c=1+((i+1)%segs); m.indices.insert(m.indices.end(),{(uint32_t)a,(uint32_t)c,(uint32_t)b});}
 m.compute_normals(); m.compute_bbox(); return m;}

MeshData make_torus(double R,double r,int n,int mseg){
 MeshData m; for(int i=0;i<n;i++){ double u=2*M_PI*i/n; for(int j=0;j<mseg;j++){ double v=2*M_PI*j/mseg;
  m.vertices.push_back({(R+r*cos(v))*cos(u), r*sin(v), (R+r*cos(v))*sin(u)});}}
 for(int i=0;i<n;i++) for(int j=0;j<mseg;j++){ int a=i*mseg+j,b=((i+1)%n)*mseg+j,c=b+((j+1)%mseg)-j,d=a+((j+1)%mseg)-j;
  m.indices.insert(m.indices.end(),{(uint32_t)a,(uint32_t)b,(uint32_t)d, (uint32_t)b,(uint32_t)c,(uint32_t)d});}
 m.compute_normals(); m.compute_bbox(); return m;}
}

