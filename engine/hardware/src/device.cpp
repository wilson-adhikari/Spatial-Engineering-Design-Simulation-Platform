#include "hardware/device.h"
namespace spatial::hardware{
DeviceManager& DeviceManager::instance(){ static DeviceManager m; return m;}
}
