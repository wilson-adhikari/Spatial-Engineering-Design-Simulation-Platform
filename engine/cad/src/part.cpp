#include "cad/part.h"
namespace spatial::cad{
std::shared_ptr<Sketch> Part::create_sketch(std::string plane){
 auto s=std::make_shared<Sketch>(); s->plane=std::move(plane); sketches.push_back(s); return s;}
std::shared_ptr<ExtrudeFeature> Part::extrude(std::shared_ptr<Sketch> s,double d){
 auto f=std::make_shared<ExtrudeFeature>(); f->sketch=s; f->distance=d; features.push_back(f); return f;}
geometry::MeshData Part::build() const{
 if(features.empty()) return {};
 auto m=features.back()->evaluate(); return m;}
scene::Mesh Part::to_mesh() const{ scene::Mesh m; m.data=build(); m.name=name; return m;}
void Part::clear(){ features.clear(); sketches.clear();}
}
