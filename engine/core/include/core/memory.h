#pragma once
#include <memory>
#include <vector>
namespace spatial::core{
template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename... Args>
Ref<T> make_ref(Args&&... args){ return std::make_shared<T>(std::forward<Args>(args)...);}
class LinearArena{
public:
 explicit LinearArena(size_t cap=1<<20):buf_(cap),offset_(0){}
 void* alloc(size_t n){ if(offset_+n>buf_.size()) return ::operator new(n); void* p=buf_.data()+offset_; offset_+=n; return p;}
 void reset(){offset_=0;}
private:
 std::vector<char> buf_;
 size_t offset_;
};
}
