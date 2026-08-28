#pragma once
#include "cad/feature.h"
#include "scene/mesh.h"
#include "core/command.h"
#include <vector>
namespace spatial::cad{
class Part{
public:
 core::Uuid id=core::Uuid::generate();
 std::string name="Part";
 std::vector<std::shared_ptr<Feature>> features;
 std::vector<std::shared_ptr<Sketch>> sketches;
 std::shared_ptr<Sketch> create_sketch(std::string plane="XY");
 std::shared_ptr<ExtrudeFeature> extrude(std::shared_ptr<Sketch> s,double dist);
 geometry::MeshData build() const;
 scene::Mesh to_mesh() const;
 void clear();
};
}
