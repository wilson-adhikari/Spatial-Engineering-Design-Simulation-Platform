#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "core/result.h"
namespace spatial::core{
class Command{
public:
 virtual ~Command()=default;
 virtual std::string name() const =0;
 virtual Result<void> execute()=0;
 virtual Result<void> undo()=0;
 virtual bool can_undo() const {return true;}
};
class CommandStack{
public:
 Result<void> execute(std::unique_ptr<Command> cmd);
 Result<void> undo();
 Result<void> redo();
 bool can_undo() const {return !undo_.empty();}
 bool can_redo() const {return !redo_.empty();}
 void clear();
 size_t size() const {return undo_.size();}
private:
 std::vector<std::unique_ptr<Command>> undo_;
 std::vector<std::unique_ptr<Command>> redo_;
};
}
