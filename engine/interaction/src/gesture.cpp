#include "interaction/gesture.h"
#include <vector>
namespace spatial::interaction{
Gesture GestureRecognizer::recognize(const std::vector<math::Vec3>& pts){
 if(pts.empty()) return {};
 return {GestureType::Point,0.8,pts[0]};
}
}
