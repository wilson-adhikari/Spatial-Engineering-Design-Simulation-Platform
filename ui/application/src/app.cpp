#include "app.h"
#include "core/logger.h"
namespace spatial::ui{
Application& Application::instance(){ static Application a; return a;}
bool Application::init(int,char**){ core::Logger::instance().log(core::LogLevel::Info,"App init"); return true;}
int Application::run(){ core::Logger::instance().log(core::LogLevel::Info,"App run - headless mode (GUI requires Qt6)"); return 0;}
void Application::shutdown(){}
}
