#pragma once
#include "robotics/kinematics.h"
namespace spatial::robotics{ struct Dynamics{ static std::vector<double> gravity_torque(const KinematicChain&);}; }
