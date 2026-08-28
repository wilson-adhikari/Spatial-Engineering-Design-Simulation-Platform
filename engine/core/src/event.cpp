#include "core/event.h"
#include <algorithm>
namespace spatial::core{
EventBus& EventBus::global(){ static EventBus b; return b;}
EventBus::Id EventBus::subscribe(std::string topic, EventCallback cb){
 Id id=next_++; subs_.push_back({id,std::move(topic),std::move(cb)}); return id;}
void EventBus::unsubscribe(Id id){
 subs_.erase(std::remove_if(subs_.begin(),subs_.end(),[id](auto& s){return s.id==id;}),subs_.end());}
void EventBus::publish(const std::string& topic, void* data){
 for(auto& s:subs_) if(s.topic==topic) s.cb(data);
}
}
