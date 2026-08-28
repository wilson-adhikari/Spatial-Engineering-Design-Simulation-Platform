#include "cad/sketch.h"
#include <stdexcept>
namespace spatial::cad{
SketchEntity& Sketch::add_line(math::Vec2 a,math::Vec2 b){
 if(!a.is_finite()||!b.is_finite()) throw std::invalid_argument("invalid line");
 if(entities.size()>=MAX_ENTITIES) throw std::runtime_error("too many entities");
 entities.push_back({}); auto& e=entities.back(); e.type="line"; e.p0=a; e.p1=b; return e;}
SketchEntity& Sketch::add_circle(math::Vec2 c,double r){
 if(!c.is_finite()||!std::isfinite(r)||r<=0||r>1e6) throw std::invalid_argument("invalid circle");
 if(entities.size()>=MAX_ENTITIES) throw std::runtime_error("too many entities");
 entities.push_back({}); auto& e=entities.back(); e.type="circle"; e.center=c; e.radius=r; return e;}
SketchEntity& Sketch::add_arc(math::Vec2 c,double r,double s,double e){
 if(!c.is_finite()||!std::isfinite(r)||r<=0||r>1e6) throw std::invalid_argument("invalid arc");
 if(entities.size()>=MAX_ENTITIES) throw std::runtime_error("too many entities");
 entities.push_back({}); auto& en=entities.back(); en.type="arc"; en.center=c; en.radius=r; en.p0={s,e}; return en;}
SketchEntity& Sketch::add_rectangle(math::Vec2 a,math::Vec2 b){
 if(!a.is_finite()||!b.is_finite()) throw std::invalid_argument("invalid rect");
 if(entities.size()+4>MAX_ENTITIES) throw std::runtime_error("too many entities");
 add_line(a,{b.x,a.y}); add_line({b.x,a.y},b); add_line(b,{a.x,b.y}); add_line({a.x,b.y},a); return entities.back();}
bool Sketch::add_constraint(Constraint c){
 if(!c.is_valid()) return false;
 if(constraints.size()>=MAX_CONSTRAINTS) return false;
 constraints.push_back(std::move(c)); return true;
}
}

