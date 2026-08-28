# Architecture
Concept doc v1.0 Section 5
"
Set-Content -Path "docs/BUILD.md" -Value "# Build
cmake --preset msvc
cmake --build build/msvc"
New-Item -ItemType Directory -Force -Path "docs" | Out-Null
New-Item -ItemType Directory -Force -Path "assets/materials" | Out-Null
Set-Content -Path "assets/materials/default.mtl" -Value "albedo 0.7 0.7 0.7"
New-Item -ItemType Directory -Force -Path "ui/themes" | Out-Null
Set-Content -Path "ui/themes/dark.json" -Value '{"name":"dark"}'
Set-Content -Path "ui/themes/light.json" -Value '{"name":"light"}'
New-Item -ItemType Directory -Force -Path "third_party" | Out-Null
Set-Content -Path "third_party/README.md" -Value "# third party"
New-Item -ItemType Directory -Force -Path "tools" | Out-Null
Set-Content -Path "tools/README.md" -Value "# tools"

# Fix missing ui include dirs
Set-Content -Path "ui/application/include/app.h" -Value @"
#pragma once
#include ""core/command.h""
#include ""scene/scene.h""
#include ""io/project.h""
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
