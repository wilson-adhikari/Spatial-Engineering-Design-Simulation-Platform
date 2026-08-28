#pragma once
#include "scene/node.h"
#include "scene/camera.h"
#include "scene/mesh.h"
#include <unordered_map>
namespace spatial::scene{
class Scene{
public:
 std::shared_ptr<Node> root = std::make_shared<Node>();
 Camera camera;
 std::unordered_map<std::string,std::shared_ptr<Mesh>> meshes;
 void add_mesh(std::shared_ptr<Mesh> m){ meshes[m->id.to_string()]=m;}
 void clear(){ root=std::make_shared<Node>(); meshes.clear();}
};
}
