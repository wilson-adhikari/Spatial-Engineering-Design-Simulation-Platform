#include "simulation/solver.h"
namespace spatial::simulation{
SolverRegistry& SolverRegistry::instance(){ static SolverRegistry r; return r;}
void SolverRegistry::register_solver(std::function<std::unique_ptr<ISolver>()> f){ factories_.push_back(f);}
std::unique_ptr<ISolver> SolverRegistry::create(const std::string& n){ for(auto& f:factories_){ auto s=f(); if(s&&s->name()==n) return s;} return nullptr;}
}
