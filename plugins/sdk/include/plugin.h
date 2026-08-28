#pragma once
#include <string>
namespace spatial::plugin{
struct PluginInfo{ std::string name, version, author;};
class IPlugin{
public:
 virtual ~IPlugin()=default;
 virtual PluginInfo info() const =0;
 virtual bool load()=0;
 virtual void unload()=0;
};
}
