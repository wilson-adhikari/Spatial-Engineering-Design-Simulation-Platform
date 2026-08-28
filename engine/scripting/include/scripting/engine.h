#pragma once
#include <string>
#include <functional>
#include <unordered_set>
namespace spatial::scripting{
enum class ScriptPermission{ None=0, FileRead=1, FileWrite=2, Network=4, System=8 };
class ScriptEngine{
public:
 ScriptEngine();
 bool exec_file(const std::string& path);
 bool exec_string(const std::string& code);
 void register_api(const std::string& name, std::function<void()> fn);
 void set_permissions(int perms){ perms_=perms; }
 bool is_enabled() const { return enabled_; }
 void set_enabled(bool e){ enabled_=e; }
private:
 bool enabled_=false;
 int perms_=0;
 std::unordered_set<std::string> allowed_apis_;
 static constexpr size_t MAX_CODE_SIZE = 1024*1024;
 bool is_safe_path(const std::string& p) const;
 bool is_safe_code(const std::string& c) const;
};
}
