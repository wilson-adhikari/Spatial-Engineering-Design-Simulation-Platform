#include "core/uuid.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <mutex>
namespace spatial::core{
Uuid Uuid::generate(){
 static std::mutex mtx;
 std::lock_guard<std::mutex> lk(mtx);
 try {
  std::random_device rd;
  std::seed_seq seq{rd(), rd(), rd(), rd(), (uint32_t)std::chrono::high_resolution_clock::now().time_since_epoch().count()};
  std::mt19937_64 rng(seq);
  return {rng(),rng()};
 } catch(...) {
  static uint64_t counter = 0;
  auto now = (uint64_t)std::chrono::high_resolution_clock::now().time_since_epoch().count();
  return {now ^ ++counter, counter * 6364136223846793005ULL};
 }
}
std::string Uuid::to_string() const{
 std::ostringstream oss;
 oss<<std::hex<<std::setw(16)<<std::setfill('0')<<hi<<std::setw(16)<<lo;
 return oss.str();
}
}
