#pragma once
#include "math/vec.h"
#include <vector>
namespace spatial::simulation{
struct RigidBody{ math::Vec3 pos{0,0,0}, vel{0,0,0}, force{0,0,0}; double mass=1; bool is_static=false;};
class PhysicsWorld{
public:
 math::Vec3 gravity{0,-9.81,0};
 void add_body(RigidBody b){ bodies_.push_back(b);}
 void step(double dt);
 const std::vector<RigidBody>& bodies() const {return bodies_;}
private:
 std::vector<RigidBody> bodies_;
};
}
