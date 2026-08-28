#pragma once
#include <string>
#include <functional>
namespace spatial::scripting{
class ScriptEngine{
public:
 bool exec_file(const std::string& path);
 bool exec_string(const std::string& code);
 void register_api(const std::string& name, std::function<void()> fn);
};
}
