#pragma once
#include "math/vec.h"
#include "core/uuid.h"
#include <vector>
#include <variant>
namespace spatial::cad{
enum class ConstraintType{Horizontal,Vertical,Coincident,Parallel,Perpendicular,Tangent,Concentric,Equal,Symmetric,Distance,Angle,Radius,Diameter,Fixed};
struct Constraint{ ConstraintType type; std::vector<core::Uuid> entities; double value=0; bool is_valid() const { return entities.size()<=2 && std::isfinite(value); } };
struct SketchEntity{
 core::Uuid id=core::Uuid::generate();
 std::string type;
 math::Vec2 p0,p1;
 math::Vec2 center; double radius=0;
 bool construction=false;
 bool is_valid() const { return p0.is_finite() && p1.is_finite() && center.is_finite() && std::isfinite(radius) && radius>=0 && radius<=1e6; }
};
class Sketch{
public:
 core::Uuid id=core::Uuid::generate();
 std::string name;
 std::string plane="XY";
 std::vector<SketchEntity> entities;
 std::vector<Constraint> constraints;
 static constexpr size_t MAX_ENTITIES = 10000;
 static constexpr size_t MAX_CONSTRAINTS = 10000;
 SketchEntity& add_line(math::Vec2 a,math::Vec2 b);
 SketchEntity& add_circle(math::Vec2 c,double r);
 SketchEntity& add_arc(math::Vec2 c,double r,double s,double e);
 SketchEntity& add_rectangle(math::Vec2 a,math::Vec2 b);
 bool add_constraint(Constraint c);
 void clear(){ entities.clear(); constraints.clear();}
 bool is_valid_plane() const { return plane=="XY"||plane=="XZ"||plane=="YZ"; }
};
}
