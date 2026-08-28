#pragma once
#include "scene/scene.h"
#include "scene/camera.h"
#include "rendering/renderer.h"
namespace spatial::viewport{
enum class ViewMode{Shaded,Wireframe,XRay,MaterialPreview};
class Viewport{
public:
 bool init(int w=1280,int h=720);
 void render(const scene::Scene& sc);
 void set_mode(ViewMode m){ mode_=m;}
 void resize(int w,int h){ width_=w; height_=h;}
 scene::Camera& camera(){return cam_;}
private:
 int width_=1280,height_=720;
 ViewMode mode_=ViewMode::Shaded;
 scene::Camera cam_;
 std::unique_ptr<rendering::IRenderer> renderer_;
};
}
