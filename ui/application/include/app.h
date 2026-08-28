#pragma once
#include "core/command.h"
#include "scene/scene.h"
#include "io/project.h"
namespace spatial::ui{
class Application{
public:
 static Application& instance();
 bool init(int argc,char** argv);
 int run();
 void shutdown();
 scene::Scene& scene(){return scene_;}
 io::Project& project(){return project_;}
 core::CommandStack& commands(){return stack_;}
private:
 scene::Scene scene_;
 io::Project project_;
 core::CommandStack stack_;
};
}

