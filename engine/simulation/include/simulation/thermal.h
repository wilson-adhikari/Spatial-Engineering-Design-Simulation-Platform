#pragma once
#include "simulation/solver.h"
namespace spatial::simulation{
class ThermalSolver : public ISolver{
public:
 std::string name() const override {return "Thermal";}
 SolverResult solve() override {return {true,"Thermal stub",{}, 0,0};}
 void set_mesh(void*) override {} void set_material(void*) override {}
};
}
