#pragma once
#include "math/vec.h"
#include <vector>
namespace spatial::vision{
struct HandPose{ std::vector<math::Vec3> joints; double confidence=0;};
class HandTracker{
public:
 bool init(int camera_id=0);
 std::vector<HandPose> track(const void* frame=nullptr);
 void shutdown();
};
}
