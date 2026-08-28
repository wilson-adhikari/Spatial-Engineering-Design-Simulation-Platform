#pragma once
#include <functional>
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
namespace spatial::core{
using EventCallback = std::function<void(void*)>;
class EventBus{
public:
 using Id = uint32_t;
 Id subscribe(std::string topic, EventCallback cb);
 void unsubscribe(Id id);
 void publish(const std::string& topic, void* data=nullptr);
 static EventBus& global();
private:
 struct Sub{Id id; std::string topic; EventCallback cb;};
 std::vector<Sub> subs_;
 Id next_=1;
};
}
