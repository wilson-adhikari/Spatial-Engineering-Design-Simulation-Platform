#pragma once
#include "cad/part.h"
namespace spatial::cad{
std::shared_ptr<Part> make_box_part(double x,double y,double z);
std::shared_ptr<Part> make_cylinder_part(double r,double h);
std::shared_ptr<Part> make_sphere_part(double r);
}
