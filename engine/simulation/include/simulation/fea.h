#pragma once
#include "simulation/solver.h"
namespace spatial::simulation{
class FEASolver : public ISolver{
public:
 std::string name() const override {return "FEA";}
 SolverResult solve() override { return {true,"FEA stub",{}, 12.5, 0.002};}
 void set_mesh(void*) override {}
 void set_material(void*) override {}
};
}
