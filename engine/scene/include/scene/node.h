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
 static constexpr size_t MAX_CHILDREN = 10000;
 bool add_child(std::shared_ptr<Node> c);
 bool set_name(const std::string& n);
 math::Mat4 world_matrix() const;
 math::Transform world_transform() const;
};
}
