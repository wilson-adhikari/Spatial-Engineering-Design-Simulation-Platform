#include "core/command.h"
namespace spatial::core{
Result<void> CommandStack::execute(std::unique_ptr<Command> cmd){
 auto r=cmd->execute();
 if(!r.is_ok()) return r;
 undo_.push_back(std::move(cmd));
 redo_.clear();
 return Result<void>::ok();
}
Result<void> CommandStack::undo(){
 if(undo_.empty()) return Result<void>::err("nothing to undo");
 auto cmd=std::move(undo_.back()); undo_.pop_back();
 auto r=cmd->undo();
 if(!r.is_ok()) return r;
 redo_.push_back(std::move(cmd));
 return Result<void>::ok();
}
Result<void> CommandStack::redo(){
 if(redo_.empty()) return Result<void>::err("nothing to redo");
 auto cmd=std::move(redo_.back()); redo_.pop_back();
 auto r=cmd->execute();
 if(!r.is_ok()) return r;
 undo_.push_back(std::move(cmd));
 return Result<void>::ok();
}
void CommandStack::clear(){ undo_.clear(); redo_.clear();}
}
