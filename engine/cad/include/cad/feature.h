#pragma once
#include "core/uuid.h"
#include "cad/sketch.h"
#include "geometry/primitives.h"
#include <string>
#include <memory>
namespace spatial::cad{
enum class FeatureType{Extrude,Revolve,Pocket,Fillet,Chamfer,Pattern,Boolean};
struct Feature{
 core::Uuid id=core::Uuid::generate();
 FeatureType type;
 std::string name;
 bool suppressed=false;
 virtual ~Feature()=default;
 virtual geometry::MeshData evaluate() const =0;
};
struct ExtrudeFeature : Feature{
 std::shared_ptr<Sketch> sketch;
 double distance=10;
 ExtrudeFeature(){ type=FeatureType::Extrude; name="Extrude";}
 geometry::MeshData evaluate() const override;
};
struct RevolveFeature : Feature{
 std::shared_ptr<Sketch> sketch;
 double angle=6.28318;
 RevolveFeature(){ type=FeatureType::Revolve; name="Revolve";}
 geometry::MeshData evaluate() const override;
};
struct BooleanFeature : Feature{
 enum Op{Union,Subtract,Intersect} op=Union;
 geometry::MeshData a,b;
 geometry::MeshData evaluate() const override;
};
}
