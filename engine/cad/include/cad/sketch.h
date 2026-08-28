#pragma once
#include "math/vec.h"
#include "core/uuid.h"
#include <vector>
#include <variant>
namespace spatial::cad{
enum class ConstraintType{Horizontal,Vertical,Coincident,Parallel,Perpendicular,Tangent,Concentric,Equal,Symmetric,Distance,Angle,Radius,Diameter,Fixed};
struct Constraint{ ConstraintType type; std::vector<core::Uuid> entities; double value=0;};
struct SketchEntity{
 core::Uuid id=core::Uuid::generate();
 std::string type;
 math::Vec2 p0,p1;
 math::Vec2 center; double radius=0;
 bool construction=false;
};
class Sketch{
public:
 core::Uuid id=core::Uuid::generate();
 std::string name;
 std::string plane="XY";
 std::vector<SketchEntity> entities;
 std::vector<Constraint> constraints;
 SketchEntity& add_line(math::Vec2 a,math::Vec2 b);
 SketchEntity& add_circle(math::Vec2 c,double r);
 SketchEntity& add_arc(math::Vec2 c,double r,double s,double e);
 SketchEntity& add_rectangle(math::Vec2 a,math::Vec2 b);
 void add_constraint(Constraint c){ constraints.push_back(std::move(c));}
 void clear(){ entities.clear(); constraints.clear();}
};
}
