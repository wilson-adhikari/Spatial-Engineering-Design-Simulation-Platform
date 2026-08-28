#include "plugin.h"
#include <filesystem>
namespace fs = std::filesystem;
namespace spatial::plugin{
PluginManager& PluginManager::instance(){ static PluginManager m; return m; }
bool PluginManager::register_plugin(const std::string& path, PluginFactory f){
 if(path.empty()||path.size()>1024) return false;
 if(path.find("..")!=std::string::npos) return false;
 if(!f) return false;
 for(auto& p: plugins_) if(p.path==path) return false;
 plugins_.push_back({path,f,false});
 return true;
}
bool PluginManager::load_plugin(const std::string& path){
 for(auto& p: plugins_) if(p.path==path){
  if(!p.verified) return false;
  auto* inst = p.factory();
  if(!inst) return false;
  bool ok = inst->load();
  delete inst;
  return ok;
 }
 return false;
}
bool PluginManager::is_verified(const std::string& path) const {
 for(auto& p: plugins_) if(p.path==path) return p.verified;
 return false;
}
}

