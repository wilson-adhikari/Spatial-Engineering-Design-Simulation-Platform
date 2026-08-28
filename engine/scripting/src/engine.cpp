#include "scripting/engine.h"
#include "core/logger.h"
#include <filesystem>
namespace fs = std::filesystem;
namespace spatial::scripting{
ScriptEngine::ScriptEngine(){}
bool ScriptEngine::is_safe_path(const std::string& p) const{
 if(p.empty()||p.size()>1024) return false;
 if(p.find("..")!=std::string::npos) return false;
 if(p.find('\0')!=std::string::npos) return false;
 fs::path path(p); if(path.is_absolute()) return false; return true;
}
bool ScriptEngine::is_safe_code(const std::string& c) const{
 if(c.size()>MAX_CODE_SIZE) return false;
 if(c.find("import os")!=std::string::npos) return false;
 if(c.find("subprocess")!=std::string::npos) return false;
 if(c.find("eval(")!=std::string::npos) return false;
 if(c.find("exec(")!=std::string::npos) return false;
 return true;
}
bool ScriptEngine::exec_file(const std::string& p){
 if(!enabled_) { core::Logger::instance().log(core::LogLevel::Warn, "scripting disabled"); return false; }
 if(!is_safe_path(p)) return false;
 if(!(perms_ & (int)ScriptPermission::FileRead)) return false;
 try{
  if(!fs::exists(p)) return false;
  if(fs::file_size(p) > MAX_CODE_SIZE) return false;
  core::Logger::instance().log(core::LogLevel::Info, std::string("exec file: ")+p);
  return true;
 } catch(...){ return false; }
}
bool ScriptEngine::exec_string(const std::string& c){
 if(!enabled_) return false;
 if(!is_safe_code(c)) return false;
 core::Logger::instance().log(core::LogLevel::Info, c.substr(0,256));
 return true;
}
void ScriptEngine::register_api(const std::string& name, std::function<void()> fn){
 if(name.empty()||name.size()>128) return;
 if(name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_")!=std::string::npos) return;
 allowed_apis_.insert(name);
}
}
