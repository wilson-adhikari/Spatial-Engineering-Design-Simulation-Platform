#pragma once
#include "math/transform.h"
#include "core/uuid.h"
#include <vector>
#include <string>
#include <memory>
namespace spatial::scene{
class Node : public std::enable_shared_from_this<Node>{
public:
 core::Uuid id=core::Uuid::generate();
 std::string name;
 math::Transform local;
 std::weak_ptr<Node> parent;
 std::vector<std::shared_ptr<Node>> children;
 void add_child(std::shared_ptr<Node> c){ c->parent=shared_from_this(); children.push_back(c);}
 math::Mat4 world_matrix() const;
 math::Transform world_transform() const;
};
}
