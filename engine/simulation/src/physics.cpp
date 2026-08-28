#include "simulation/physics.h"
namespace spatial::simulation{
void PhysicsWorld::step(double dt){
 for(auto& b:bodies_){ if(b.is_static) continue; b.vel=b.vel+gravity*dt; b.vel=b.vel+b.force*(dt/b.mass); b.pos=b.pos+b.vel*dt; b.force={0,0,0};}
}
}
