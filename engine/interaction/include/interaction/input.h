#pragma once
#include "interaction/gesture.h"
#include "core/event.h"
namespace spatial::interaction{
struct InputState{ math::Vec3 cursor{0,0,0}; bool left_down=false; Gesture gesture;};
class InputSystem{
public:
 void update(const InputState& s){ state_=s; if(s.left_down) core::EventBus::global().publish("input.click");}
 const InputState& state() const {return state_;}
private:
 InputState state_;
};
}
