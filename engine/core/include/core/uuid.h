#pragma once
#include <string>
#include <cstdint>
namespace spatial::core{
struct Uuid{
 uint64_t hi=0,lo=0;
 static Uuid generate();
 std::string to_string() const;
 bool operator==(const Uuid& o) const {return hi==o.hi && lo==o.lo;}
};
}
namespace std{template<> struct hash<spatial::core::Uuid>{ size_t operator()(spatial::core::Uuid const& u) const noexcept {return hash<uint64_t>{}(u.hi ^ u.lo);} };}
