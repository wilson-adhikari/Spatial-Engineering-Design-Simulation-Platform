#include "core/logger.h"
namespace spatial::core{
Logger& Logger::instance(){ static Logger l; return l;}
void Logger::log(LogLevel lvl,std::string_view msg){
 if(lvl<level_) return;
 const char* tag[]={"TRACE","DEBUG","INFO","WARN","ERROR"};
 std::cout<<"["<<tag[(int)lvl]<<"] "<<msg<<"\n";
}
}
