#pragma once
#include "math/vec.h"
#include <vector>
#include <stdexcept>
namespace spatial::simulation{
struct RigidBody{
 math::Vec3 pos{0,0,0}, vel{0,0,0}, force{0,0,0};
 double mass=1;
 bool is_static=false;
 bool is_valid() const { return pos.is_finite()&&vel.is_finite()&&force.is_finite()&&std::isfinite(mass)&&mass>=0; }
};
class PhysicsWorld{
public:
 math::Vec3 gravity{0,-9.81,0};
 static constexpr size_t MAX_BODIES = 10000;
 void add_body(RigidBody b){
  if(!b.is_valid()) throw std::invalid_argument("invalid body");
  if(bodies_.size() >= MAX_BODIES) throw std::runtime_error("too many bodies");
  if(b.mass<1e-9 && !b.is_static) throw std::invalid_argument("mass too small");
  bodies_.push_back(b);
 }
 void step(double dt);
 const std::vector<RigidBody>& bodies() const {return bodies_;}
 size_t count() const { return bodies_.size(); }
 void clear(){ bodies_.clear(); }
private:
 std::vector<RigidBody> bodies_;
};
}
