#pragma once
#include <string>
#include <vector>
#include <mutex>
namespace spatial::hardware{
enum class DeviceClass{Camera,Display,Sensor,Controller,IMU,Haptic,Tracking,Custom};
struct DeviceInfo{ std::string id,name; DeviceClass cls; bool connected=false; bool requires_permission=true; };
class Device{
public:
 virtual ~Device()=default;
 virtual DeviceInfo info() const =0;
 virtual bool connect()=0;
 virtual void disconnect()=0;
 virtual bool is_connected() const =0;
 virtual bool has_permission() const { return true; }
};
class DeviceManager{
public:
 static DeviceManager& instance();
 bool request_permission(const std::string& id);
 void register_device(DeviceInfo i);
 std::vector<DeviceInfo> list() const;
 bool connect_device(const std::string& id);
private:
 mutable std::mutex mutex_;
 std::vector<DeviceInfo> devices_;
};
}
