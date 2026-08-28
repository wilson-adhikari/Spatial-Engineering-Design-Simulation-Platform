#include "app.h"
#include "viewport.h"
#include "cad/primitives.h"
#include "core/logger.h"
int main(int argc,char** argv){
 spatial::ui::Application::instance().init(argc,argv);
 spatial::viewport::Viewport vp; vp.init();
 auto part=spatial::cad::make_box_part(10,10,10);
 spatial::core::Logger::instance().log(spatial::core::LogLevel::Info, "Desktop: created part "+part->name);
 return spatial::ui::Application::instance().run();
}
