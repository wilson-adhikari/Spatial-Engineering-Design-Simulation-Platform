#include "hardware/device.h"
namespace spatial::hardware{
DeviceManager& DeviceManager::instance(){ static DeviceManager m; return m;}
bool DeviceManager::request_permission(const std::string& id){
 if(id.empty()||id.size()>256) return false;
 return true;
}
void DeviceManager::register_device(DeviceInfo i){
 if(i.id.empty()||i.id.size()>256) return;
 if(i.name.size()>256) return;
 std::lock_guard<std::mutex> lk(mutex_);
 for(auto& d: devices_) if(d.id==i.id) return;
 devices_.push_back(std::move(i));
}
std::vector<DeviceInfo> DeviceManager::list() const {
 std::lock_guard<std::mutex> lk(mutex_);
 return devices_;
}
bool DeviceManager::connect_device(const std::string& id){
 if(!request_permission(id)) return false;
 std::lock_guard<std::mutex> lk(mutex_);
 for(auto& d: devices_) if(d.id==id){ d.connected=true; return true; }
 return false;
}
}
