#pragma once
#include <string>
#include <vector>
#include <memory>
#include <mutex>
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
 bool can_undo() const;
 bool can_redo() const;
 void clear();
 size_t size() const;
private:
 static constexpr size_t MAX_STACK = 1000;
 mutable std::mutex mutex_;
 std::vector<std::unique_ptr<Command>> undo_;
 std::vector<std::unique_ptr<Command>> redo_;
};
}
