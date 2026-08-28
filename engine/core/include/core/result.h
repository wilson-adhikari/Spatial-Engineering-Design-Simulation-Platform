#pragma once
#include <optional>
#include <string>
#include <variant>
namespace spatial::core{
template<typename T>
class Result{
public:
 static Result ok(T v){ return Result(std::move(v));}
 static Result err(std::string e){ Result r; r.error_=std::move(e); r.has_value_=false; return r;}
 bool is_ok() const {return has_value_;}
 bool is_err() const {return !has_value_;}
 T& value(){return *value_;}
 const std::string& error() const {return error_;}
private:
 Result(T v):value_(std::move(v)),has_value_(true){}
 Result(){}
 std::optional<T> value_;
 std::string error_;
 bool has_value_=false;
};
template<>
class Result<void>{
public:
 static Result ok(){ Result r; r.has_value_=true; return r;}
 static Result err(std::string e){ Result r; r.error_=std::move(e); return r;}
 bool is_ok() const {return has_value_;}
 const std::string& error() const {return error_;}
private:
 bool has_value_=false;
 std::string error_;
};
}
