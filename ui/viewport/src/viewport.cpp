#include "viewport.h"
#include <stdexcept>
namespace spatial::viewport{
bool Viewport::init(int w,int h){
 if(w<MIN_SIZE||w>MAX_SIZE||h<MIN_SIZE||h>MAX_SIZE) return false;
 width_=w; height_=h;
 renderer_=rendering::create_renderer();
 if(!renderer_) return false;
 return renderer_->init();
}
void Viewport::render(const scene::Scene& sc){
 if(!renderer_) return;
 if(sc.root && sc.root->children.size()>10000) return;
 renderer_->begin_frame();
 renderer_->draw_scene(sc);
 renderer_->end_frame();
}
}

