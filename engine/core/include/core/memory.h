#pragma once
#include <memory>
#include <vector>
#include <cstddef>
#include <mutex>
#include <stdexcept>
namespace spatial::core{
template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename... Args>
Ref<T> make_ref(Args&&... args){ return std::make_shared<T>(std::forward<Args>(args)...);}
class LinearArena{
public:
 explicit LinearArena(size_t cap=1<<20){
  if(cap==0||cap> (1<<28)) throw std::invalid_argument("arena cap out of range");
  buf_.resize(cap); offset_=0;
 }
 ~LinearArena(){ for(auto p: heap_allocs_) ::operator delete(p); }
 LinearArena(const LinearArena&) = delete;
 LinearArena& operator=(const LinearArena&) = delete;
 void* alloc(size_t n){
  if(n==0) return nullptr;
  if(n> (1<<26)) throw std::bad_alloc();
  std::lock_guard<std::mutex> lk(mutex_);
  if(offset_+n <= buf_.size()){ void* p=buf_.data()+offset_; offset_+=n; return p; }
  void* p=::operator new(n); heap_allocs_.push_back(p); return p;
 }
 void reset(){ std::lock_guard<std::mutex> lk(mutex_); offset_=0; }
 size_t capacity() const { return buf_.size(); }
 size_t used() const { return offset_; }
private:
 std::vector<char> buf_;
 size_t offset_=0;
 std::vector<void*> heap_allocs_;
 std::mutex mutex_;
};
}

