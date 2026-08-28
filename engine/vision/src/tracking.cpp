#include "vision/tracking.h"
namespace spatial::vision{
bool HandTracker::init(int){ return true;}
std::vector<HandPose> HandTracker::track(const void*){ return {{{{0,0,0},{1,0,0}},0.9}};}
void HandTracker::shutdown(){}
}
