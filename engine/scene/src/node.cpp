#include "scene/node.h"
namespace spatial::scene{
math::Mat4 Node::world_matrix() const{
 auto m=local.matrix();
 if(auto p=parent.lock()) return p->world_matrix()*m;
 return m;
}
math::Transform Node::world_transform() const{
 if(auto p=parent.lock()) return p->world_transform()*local;
 return local;
}
}
