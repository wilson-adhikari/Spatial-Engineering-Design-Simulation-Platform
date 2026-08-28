#pragma once
#include <string>
#include <functional>
namespace spatial::plugin{
struct PluginInfo{ std::string name, version, author; bool is_verified=false; };
class IPlugin{
public:
 virtual ~IPlugin()=default;
 virtual PluginInfo info() const =0;
 virtual bool load()=0;
 virtual void unload()=0;
 virtual bool verify_signature(const std::string& pubkey) const { (void)pubkey; return false; }
};
using PluginFactory = std::function<IPlugin*()>;
class PluginManager{
public:
 static PluginManager& instance();
 bool register_plugin(const std::string& path, PluginFactory f);
 bool load_plugin(const std::string& path);
 bool is_verified(const std::string& path) const;
private:
 struct Entry{ std::string path; PluginFactory factory; bool verified=false; };
 std::vector<Entry> plugins_;
};
}

