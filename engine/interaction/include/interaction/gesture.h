#pragma once
#include "math/vec.h"
#include <string>
#include <vector>
namespace spatial::interaction{
enum class GestureType{None,Grab,Pinch,Point,Swipe,Rotate,Scale};
struct Gesture{ GestureType type=GestureType::None; double confidence=0; math::Vec3 pos{0,0,0};};
class GestureRecognizer{
public:
 Gesture recognize(const std::vector<math::Vec3>& hand_points);
};
}
