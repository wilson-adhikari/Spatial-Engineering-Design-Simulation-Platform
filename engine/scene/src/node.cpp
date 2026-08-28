#include "scene/node.h"
#include <stdexcept>
#include <unordered_set>
namespace spatial::scene{
static constexpr int MAX_DEPTH = 128;
bool Node::add_child(std::shared_ptr<Node> c){
 if(!c) return false;
 if(c.get()==this) return false;
 if(children.size()>=MAX_CHILDREN) return false;
 if(c->name.size()>256) return false;
 c->parent=shared_from_this();
 children.push_back(c);
 return true;
}
bool Node::set_name(const std::string& n){
 if(n.size()>256) return false;
 for(char ch: n) if(ch=='\0') return false;
 name=n; return true;
}
math::Mat4 Node::world_matrix() const{
 math::Mat4 m=local.matrix();
 auto cur = parent.lock();
 int depth=0;
 std::unordered_set<const Node*> visited;
 visited.insert(this);
 while(cur){
  if(depth++ > MAX_DEPTH) throw std::runtime_error("scene graph depth overflow");
  if(visited.count(cur.get())) throw std::runtime_error("scene cycle");
  visited.insert(cur.get());
  m = cur->local.matrix() * m;
  cur = cur->parent.lock();
 }
 return m;
}
math::Transform Node::world_transform() const{
 auto m = world_matrix();
 return math::Transform::from_matrix(m);
}
}
