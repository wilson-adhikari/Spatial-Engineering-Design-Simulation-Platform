#include "simulation/physics.h"
#include <cmath>
namespace spatial::simulation{
void PhysicsWorld::step(double dt){
 if(!std::isfinite(dt)||dt<=0||dt>1.0) return;
 if(!gravity.is_finite()) return;
 for(auto& b:bodies_){
  if(b.is_static) continue;
  if(!b.is_valid()) continue;
  if(b.mass < 1e-9) continue;
  b.vel=b.vel+gravity*dt;
  b.vel=b.vel+b.force*(dt/b.mass);
  if(!b.vel.is_finite()){ b.vel={0,0,0}; continue; }
  b.pos=b.pos+b.vel*dt;
  if(!b.pos.is_finite()){ b.pos={0,0,0}; b.vel={0,0,0}; }
  b.force={0,0,0};
 }
}
}
