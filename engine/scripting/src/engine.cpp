#include "scripting/engine.h"
#include "core/logger.h"
namespace spatial::scripting{
bool ScriptEngine::exec_file(const std::string& p){ core::Logger::instance().log(core::LogLevel::Info, std::string("exec file: ")+p); return true;}
bool ScriptEngine::exec_string(const std::string& c){ core::Logger::instance().log(core::LogLevel::Info, c); return true;}
void ScriptEngine::register_api(const std::string&, std::function<void()>){ }
}
