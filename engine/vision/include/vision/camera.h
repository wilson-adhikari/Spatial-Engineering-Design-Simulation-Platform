#pragma once
#include <string>
namespace spatial::vision{
struct CameraInfo{ std::string name; int id=0; int width=1280,height=720; double fps=30;};
class CameraSystem{
public:
 bool open(int id);
 void close();
 bool is_open() const {return open_;}
private:
 bool open_=false;
};
}
