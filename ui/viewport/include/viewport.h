#pragma once
#include "scene/scene.h"
#include "scene/camera.h"
#include "rendering/renderer.h"
namespace spatial::viewport{
enum class ViewMode{Shaded,Wireframe,XRay,MaterialPreview};
class Viewport{
public:
 static constexpr int MIN_SIZE=64, MAX_SIZE=8192;
 bool init(int w=1280,int h=720);
 void render(const scene::Scene& sc);
 bool set_mode(ViewMode m){ mode_=m; return true; }
 bool resize(int w,int h){
  if(w<MIN_SIZE||w>MAX_SIZE||h<MIN_SIZE||h>MAX_SIZE) return false;
  width_=w; height_=h; return true;
 }
 scene::Camera& camera(){return cam_;}
 int width() const {return width_;}
 int height() const {return height_;}
private:
 int width_=1280,height_=720;
 ViewMode mode_=ViewMode::Shaded;
 scene::Camera cam_;
 std::unique_ptr<rendering::IRenderer> renderer_;
};
}

