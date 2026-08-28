#include "cad/part.h"
#include "cad/primitives.h"
#include <cassert>
#include <iostream>
int main(){
 auto part=spatial::cad::make_box_part(10,10,10);
 auto mesh=part->build();
 assert(!mesh.vertices.empty());
 auto p=std::make_shared<spatial::cad::Part>();
 auto s=p->create_sketch("XY");
 s->add_circle({0,0},5);
 p->extrude(s,20);
 assert(p->features.size()==1);
 std::cout<<"cad tests passed\n";
 return 0;
}
