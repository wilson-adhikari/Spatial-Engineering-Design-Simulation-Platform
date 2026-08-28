#include "vision/camera.h"
namespace spatial::vision{
bool CameraSystem::open(int){ open_=true; return true;}
void CameraSystem::close(){ open_=false;}
}
