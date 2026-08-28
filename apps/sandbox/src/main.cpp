#include "scene/scene.h"
#include "rendering/renderer.h"
#include "simulation/physics.h"
#include <iostream>
int main(){
 std::cout<<"Spatial Sandbox\n";
 spatial::scene::Scene sc;
 auto r=spatial::rendering::create_renderer();
 r->init(); r->begin_frame(); r->draw_scene(sc); r->end_frame();
 spatial::simulation::PhysicsWorld world; world.add_body({}); world.step(0.016);
 std::cout<<"Sandbox OK\n"; return 0;
}
