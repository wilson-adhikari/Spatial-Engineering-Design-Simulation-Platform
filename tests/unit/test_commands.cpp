#include "core/command.h"
#include <cassert>
#include <iostream>
struct IncCmd : spatial::core::Command{
 int& v; IncCmd(int& vv):v(vv){}
 std::string name() const override {return "Inc";}
 spatial::core::Result<void> execute() override {v++; return spatial::core::Result<void>::ok();}
 spatial::core::Result<void> undo() override {v--; return spatial::core::Result<void>::ok();}
};
int main(){
 spatial::core::CommandStack s;
 int v=0;
 s.execute(std::make_unique<IncCmd>(v));
 assert(v==1);
 s.undo();
 assert(v==0);
 s.redo();
 assert(v==1);
 std::cout<<"command tests passed\n";
 return 0;
}
