#pragma once
#include <string>
#include <string_view>
#include <iostream>
#include <chrono>
namespace spatial::core {
enum class LogLevel{Trace,Debug,Info,Warn,Error};
class Logger{
public:
 static Logger& instance();
 void log(LogLevel lvl,std::string_view msg);
 void set_level(LogLevel l){level_=l;}
private:
 LogLevel level_=LogLevel::Info;
};
#define SPATIAL_LOG_INFO(m) spatial::core::Logger::instance().log(spatial::core::LogLevel::Info,m)
#define SPATIAL_LOG_WARN(m) spatial::core::Logger::instance().log(spatial::core::LogLevel::Warn,m)
#define SPATIAL_LOG_ERROR(m) spatial::core::Logger::instance().log(spatial::core::LogLevel::Error,m)
}
