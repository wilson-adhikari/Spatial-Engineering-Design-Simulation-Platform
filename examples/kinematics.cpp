#include "robotics/kinematics.h"
int main(){ spatial::robotics::KinematicChain c; c.add_joint({}); auto m=c.forward(); return 0; }
