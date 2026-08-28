#include "cad/sketch.h"
namespace spatial::cad{
SketchEntity& Sketch::add_line(math::Vec2 a,math::Vec2 b){ entities.push_back({}); auto& e=entities.back(); e.type="line"; e.p0=a; e.p1=b; return e;}
SketchEntity& Sketch::add_circle(math::Vec2 c,double r){ entities.push_back({}); auto& e=entities.back(); e.type="circle"; e.center=c; e.radius=r; return e;}
SketchEntity& Sketch::add_arc(math::Vec2 c,double r,double s,double e){ entities.push_back({}); auto& en=entities.back(); en.type="arc"; en.center=c; en.radius=r; en.p0={s,e}; return en;}
SketchEntity& Sketch::add_rectangle(math::Vec2 a,math::Vec2 b){
 add_line(a,{b.x,a.y}); add_line({b.x,a.y},b); add_line(b,{a.x,b.y}); add_line({a.x,b.y},a); return entities.back();}
}
