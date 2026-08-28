#include "core/command.h"
namespace spatial::core{
Result<void> CommandStack::execute(std::unique_ptr<Command> cmd){
 if(!cmd) return Result<void>::err("null command");
 std::lock_guard<std::mutex> lk(mutex_);
 if(undo_.size() >= MAX_STACK) return Result<void>::err("command stack overflow");
 auto r=cmd->execute();
 if(!r.is_ok()) return r;
 undo_.push_back(std::move(cmd));
 redo_.clear();
 return Result<void>::ok();
}
Result<void> CommandStack::undo(){
 std::lock_guard<std::mutex> lk(mutex_);
 if(undo_.empty()) return Result<void>::err("nothing to undo");
 auto cmd=std::move(undo_.back()); undo_.pop_back();
 auto r=cmd->undo();
 if(!r.is_ok()){ undo_.push_back(std::move(cmd)); return r; }
 redo_.push_back(std::move(cmd));
 return Result<void>::ok();
}
Result<void> CommandStack::redo(){
 std::lock_guard<std::mutex> lk(mutex_);
 if(redo_.empty()) return Result<void>::err("nothing to redo");
 auto cmd=std::move(redo_.back()); redo_.pop_back();
 auto r=cmd->execute();
 if(!r.is_ok()){ redo_.push_back(std::move(cmd)); return r; }
 undo_.push_back(std::move(cmd));
 return Result<void>::ok();
}
void CommandStack::clear(){ std::lock_guard<std::mutex> lk(mutex_); undo_.clear(); redo_.clear();}
bool CommandStack::can_undo() const { std::lock_guard<std::mutex> lk(mutex_); return !undo_.empty();}
bool CommandStack::can_redo() const { std::lock_guard<std::mutex> lk(mutex_); return !redo_.empty();}
size_t CommandStack::size() const { std::lock_guard<std::mutex> lk(mutex_); return undo_.size();}
}
