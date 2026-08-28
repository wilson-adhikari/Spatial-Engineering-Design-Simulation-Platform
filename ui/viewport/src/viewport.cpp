#include "viewport.h"
namespace spatial::viewport{
bool Viewport::init(int w,int h){ width_=w; height_=h; renderer_=rendering::create_renderer(); return renderer_->init(); }
void Viewport::render(const scene::Scene& sc){ if(renderer_){ renderer_->begin_frame(); renderer_->draw_scene(sc); renderer_->end_frame();}}
}
