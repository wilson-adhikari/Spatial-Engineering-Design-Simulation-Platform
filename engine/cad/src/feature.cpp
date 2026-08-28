#include "cad/feature.h"
namespace spatial::cad{
geometry::MeshData ExtrudeFeature::evaluate() const { return geometry::make_box({10,10,distance});}
geometry::MeshData RevolveFeature::evaluate() const { return geometry::make_cylinder(5,10,32);}
geometry::MeshData BooleanFeature::evaluate() const { return a;}
}

