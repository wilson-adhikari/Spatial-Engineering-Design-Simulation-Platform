#include "cad/part.h"
#include <stdexcept>
namespace spatial::cad{
std::shared_ptr<Sketch> Part::create_sketch(std::string plane){
 if(plane!="XY"&&plane!="XZ"&&plane!="YZ") throw std::invalid_argument("invalid plane");
 if(sketches.size()>=1000) throw std::runtime_error("too many sketches");
 auto s=std::make_shared<Sketch>(); s->plane=std::move(plane); sketches.push_back(s); return s;}
std::shared_ptr<ExtrudeFeature> Part::extrude(std::shared_ptr<Sketch> s,double d){
 if(!s) throw std::invalid_argument("null sketch");
 if(!std::isfinite(d)||d==0||std::abs(d)>1e6) throw std::invalid_argument("invalid extrude distance");
 if(features.size()>=1000) throw std::runtime_error("too many features");
 auto f=std::make_shared<ExtrudeFeature>(); f->sketch=s; f->distance=d; features.push_back(f); return f;}
geometry::MeshData Part::build() const{
 if(features.empty()) return {};
 if(features.size()>1000) throw std::runtime_error("too many features");
 auto m=features.back()->evaluate();
 if(m.vertices.size()>1000000) throw std::runtime_error("mesh too large");
 return m;}
scene::Mesh Part::to_mesh() const{
 if(name.size()>256) throw std::invalid_argument("name too long");
 scene::Mesh m; m.data=build(); m.name=name; return m;}
void Part::clear(){ features.clear(); sketches.clear();}
}
