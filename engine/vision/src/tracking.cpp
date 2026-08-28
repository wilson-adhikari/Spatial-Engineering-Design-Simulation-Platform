#include "vision/tracking.h"
#include <stdexcept>
namespace spatial::vision{
bool HandTracker::init(int camera_id){
 if(camera_id<0||camera_id>16) return false;
 return true;
}
std::vector<HandPose> HandTracker::track(const void* frame){
 if(!frame) return {};
 static constexpr size_t MAX_JOINTS=64;
 std::vector<HandPose> res;
 HandPose p;
 p.joints = {{0,0,0},{1,0,0}};
 if(p.joints.size()>MAX_JOINTS) return {};
 for(auto& j: p.joints) if(!j.is_finite()) return {};
 p.confidence=0.9;
 if(p.confidence<0||p.confidence>1) p.confidence=0;
 res.push_back(p);
 if(res.size()>4) res.resize(4);
 return res;
}
void HandTracker::shutdown(){}
}

