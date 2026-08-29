#include "geometry/primitives.h"
#include <chrono>
#include <iostream>
int main(){
 auto t0=std::chrono::high_resolution_clock::now();
 for(int i=0;i<1000;i++) auto m=spatial::geometry::make_box({1,1,1});
 auto t1=std::chrono::high_resolution_clock::now();
 std::cout<<"bench make_box 1k: "<<std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count()<<"us\n";
 return 0;
}
