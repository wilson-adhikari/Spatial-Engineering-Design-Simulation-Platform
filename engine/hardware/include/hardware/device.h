#pragma once
#include <string>
#include <vector>
namespace spatial::hardware{
enum class DeviceClass{Camera,Display,Sensor,Controller,IMU,Haptic,Tracking,Custom};
struct DeviceInfo{ std::string id,name; DeviceClass cls; bool connected=false;};
class Device{
public:
 virtual ~Device()=default;
 virtual DeviceInfo info() const =0;
 virtual bool connect()=0;
 virtual void disconnect()=0;
 virtual bool is_connected() const =0;
};
class DeviceManager{
public:
 static DeviceManager& instance();
 void register_device(DeviceInfo i){ devices_.push_back(i);}
 std::vector<DeviceInfo> list() const {return devices_;}
private:
 std::vector<DeviceInfo> devices_;
};
}
