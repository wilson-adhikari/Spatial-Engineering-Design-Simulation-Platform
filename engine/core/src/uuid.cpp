#include "core/uuid.h"
#include <random>
#include <sstream>
#include <iomanip>
namespace spatial::core{
Uuid Uuid::generate(){
 static std::mt19937_64 rng{std::random_device{}()};
 return {rng(),rng()};
}
std::string Uuid::to_string() const{
 std::ostringstream oss;
 oss<<std::hex<<std::setw(16)<<std::setfill('0')<<hi<<std::setw(16)<<lo;
 return oss.str();
}
}
