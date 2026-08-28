#include "cad/primitives.h"
namespace spatial::cad{
std::shared_ptr<Part> make_box_part(double x,double y,double z){
 auto p=std::make_shared<Part>(); auto s=p->create_sketch("XY"); s->add_rectangle({-x/2,-y/2},{x/2,y/2}); p->extrude(s,z); return p;}
std::shared_ptr<Part> make_cylinder_part(double r,double h){
 auto p=std::make_shared<Part>(); auto s=p->create_sketch("XY"); s->add_circle({0,0},r); p->extrude(s,h); return p;}
std::shared_ptr<Part> make_sphere_part(double){ return std::make_shared<Part>();}
}
