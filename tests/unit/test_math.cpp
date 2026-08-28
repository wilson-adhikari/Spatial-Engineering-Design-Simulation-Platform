#include "math/vec.h"
#include "math/mat.h"
#include "math/quat.h"
#include <cassert>
#include <iostream>
int main(){
 using namespace spatial::math;
 Vec3 a{1,0,0}, b{0,1,0};
 assert((a.cross(b).z - 1) < 1e-9);
 auto t=Mat4::translate({1,2,3});
 auto p=t.transform_point({0,0,0});
 assert(p.x==1 && p.y==2 && p.z==3);
 auto q=Quat::from_axis_angle({0,0,1}, 3.14159);
 auto qm=q.to_mat4();
 (void)qm;
 std::cout<<"math tests passed\n";
 return 0;
}
