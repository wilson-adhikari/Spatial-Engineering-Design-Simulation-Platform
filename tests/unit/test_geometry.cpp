#include "geometry/primitives.h"
#include <cassert>
#include <iostream>
int main(){
 auto box=spatial::geometry::make_box({1,1,1});
 assert(!box.vertices.empty());
 auto sph=spatial::geometry::make_sphere(1,8,16);
 assert(sph.vertices.size()>0);
 std::cout<<"geometry tests passed\n";
 return 0;
}
